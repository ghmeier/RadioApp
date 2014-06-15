#include "s3e.h"
#include "s3eAudio.h"
#include "IwUtil.h"
#include "audioStreamer.h"

//Stuff for calculating mp3 frame size and validity, taken from 
//http://www.hydrogenaud.io/forums/index.php?showtopic=85125
// Bitrates - use [version][layer][bitrate]
const uint16_t mpeg_bitrates[4][4][16] = {
		{ // Version 2.5
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Reserved
			{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0 }, // Layer 3
			{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0 }, // Layer 2
			{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, 0 }  // Layer 1
		},
		{ // Reserved
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Invalid
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Invalid
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Invalid
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // Invalid
		},
		{ // Version 2
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Reserved
			{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0 }, // Layer 3
			{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0 }, // Layer 2
			{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, 0 }  // Layer 1
		},
		{ // Version 1
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Reserved
			{ 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0 }, // Layer 3
			{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 0 }, // Layer 2
			{ 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0 }, // Layer 1
		}
};
// Sample rates - use [version][srate]
const uint16_t mpeg_srates[4][4] = {
		{ 11025, 12000, 8000, 0 }, // MPEG 2.5
		{ 0, 0, 0, 0 }, // Reserved
		{ 22050, 24000, 16000, 0 }, // MPEG 2
		{ 44100, 48000, 32000, 0 }  // MPEG 1
};
// Samples per frame - use [version][layer]
const uint16_t mpeg_frame_samples[4][4] = {
	//    Rsvd     3     2     1  < Layer  v Version
		{ 0, 576, 1152, 384 }, //       2.5
		{ 0, 0, 0, 0 }, //       Reserved
		{ 0, 576, 1152, 384 }, //       2
		{ 0, 1152, 1152, 384 }  //       1
};
// Slot size (MPEG unit of measurement) - use [layer]
const uint8_t mpeg_slot_size[4] = { 0, 1, 1, 4 }; // Rsvd, 3, 2, 1
uint16_t mpg_get_frame_size(char *hdr) {
	// Quick validity check
	if ((((unsigned char)hdr[0] & 0xFF) != 0xFF)
		|| (((unsigned char)hdr[1] & 0xE0) != 0xE0)   // 3 sync bits
		|| (((unsigned char)hdr[1] & 0x18) == 0x08)   // Version rsvd
		|| (((unsigned char)hdr[1] & 0x06) == 0x00)   // Layer rsvd
		|| (((unsigned char)hdr[2] & 0xF0) == 0xF0)   // Bitrate rsvd
		) return 0;
	// Data to be extracted from the header
	uint8_t   ver = (hdr[1] & 0x18) >> 3;   // Version index
	uint8_t   lyr = (hdr[1] & 0x06) >> 1;   // Layer index
	uint8_t   pad = (hdr[2] & 0x02) >> 1;   // Padding? 0/1
	uint8_t   brx = (hdr[2] & 0xf0) >> 4;   // Bitrate index
	uint8_t   srx = (hdr[2] & 0x0c) >> 2;   // SampRate index
	// Lookup real values of these fields
	uint32_t  bitrate = mpeg_bitrates[ver][lyr][brx] * 1000;
	uint32_t  samprate = mpeg_srates[ver][srx];
	uint16_t  samples = mpeg_frame_samples[ver][lyr];
	uint8_t   slot_size = mpeg_slot_size[lyr];
	// In-between calculations
	float     bps = (float)samples / 8.0;
	float     fsize = ((bps * (float)bitrate) / (float)samprate)
		+ ((pad) ? slot_size : 0);
	// Frame sizes are truncated integers
	return (uint16_t)fsize;
}


typedef struct soundSegment{
	char *buff;
	int start;
	int len;
	int channel;
	bool ready = false;
	void play(){
		if (ready){
			s3eAudioSetInt(S3E_AUDIO_CHANNEL, channel); 
			s3eAudioPlayFromBuffer(buff + start, len + 2048, 1); 
			ready = false;
		}
	}
} soundSegment;


int alignFrames(soundSegment *seg)
{
	int start = -1, i = 0;
	for (int size = 0;; i += size){
		//Find the start of the frame, and make sure it's valid
		for (; i < seg->len && (size = mpg_get_frame_size(seg->buff + i)) == 0; i++);
		if (start < 0) start = i;
		if (i + size >= seg->len) break;
	}
	seg->start = start;
	seg->len -= start;
	seg->ready = true;
	return i;
}

bool streaming = false;

void* streamAudio(void *s)
{
	streaming = true;
	s3eSocket *sock = (s3eSocket*)s;
	const int socketBuff = 512;
	const int soundBuff = 65536;
	const int numSegs = 3;

	char *msg("GET / HTTP/1.1\n\n"); //Ask server for data
	s3eSocketSend(sock, msg, 16, 0);

	char buff[socketBuff];
	char *sound = new char[soundBuff];
	int soundLen = 0;

	soundSegment segments[numSegs];
	int currentSeg = 0;
	for (int i = 0; i < numSegs; i++) { segments[i].buff = new char[soundBuff+4096]; segments[i].channel = i % 3; }

	while (streaming){
		int len;
		while (streaming && (len = s3eSocketRecv(sock, buff, socketBuff, 0)) == -1);
		if (streaming){
			if (soundLen + len >= soundBuff){
				currentSeg = (currentSeg + 1) % numSegs;
				memcpy(segments[currentSeg].buff, sound, soundLen);
				segments[currentSeg].len = soundLen;
				int i = alignFrames(&segments[currentSeg]);
				memcpy(sound, sound + i, soundLen - i);
				soundLen -= i;
				segments[currentSeg].play();
			}
			soundSegment lastseg = segments[currentSeg];
			if (lastseg.len > 0 && lastseg.start + lastseg.len + len < soundBuff + 4096){
				memcpy(lastseg.buff + lastseg.start + lastseg.len, buff, len);
				lastseg.len += len;
			}
			memcpy(sound + soundLen, buff, len);
			soundLen += len;
		}
	}
	s3eAudioStop();
	delete[] sound;
	for (int i = 0; i < numSegs; i++) delete[] segments[i].buff;
	return 0;
}

int socketCB(s3eSocket *sock, void* sys, void* data)
{
	s3eResult res = *(s3eResult*)sys;
	if (res == S3E_RESULT_SUCCESS) s3eThreadCreate(streamAudio, sock);
	return 0;
}

void* waitForAudioStart(void *cb)
{
	//This is really unsafe and bad, but maybe works?
	void(*callback)() = 0;
	*reinterpret_cast<void**>(&callback) = cb;
	while (!s3eAudioIsPlaying() && s3eAudioGetInt(S3E_AUDIO_STATUS) != S3E_AUDIO_FAILED) s3eDeviceYield(0);
	callback();
	return 0;
}

s3eThread *waitForStartThread;

void* startNativeStreaming(void *u)
{
	char *url = (char*)u;
	s3eAudioPlay(url, 1);
	delete[] url;
	return 0;
}

void startStreamingAudio(char *ip, int port, void (*callback)())
{
	if (s3eAudioGetInt(S3E_AUDIO_PLAYBACK_FROM_HTTP_AVAILABLE) == 1){
		char *url = new char[128];
		sprintf(url, "http://%s:%d", ip, port);
		s3eThreadCreate(startNativeStreaming, url);
	}
	else{
		s3eSocket *sock = s3eSocketCreate(S3E_SOCKET_TCP);
		s3eInetAddress addr;
		if (s3eInetLookup(ip, &addr, NULL, NULL) == S3E_RESULT_ERROR) return;
		addr.m_Port = s3eInetHtons(port);
		s3eSocketConnect(sock, &addr, &socketCB, NULL);
	}
	//This is really unsafe and bad, but maybe works?
	if (callback != NULL){
		void* cb = reinterpret_cast<void*>(callback);
		waitForStartThread = s3eThreadCreate(waitForAudioStart, cb);
	}
}

void stopStreamingAudio()
{
	if(waitForStartThread != NULL) s3eThreadCancel(waitForStartThread);
	s3eAudioStop();
	streaming = false;
}
