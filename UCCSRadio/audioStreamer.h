#if !defined(__AUDIO_STREAMER_H__)
#define __AUDIO_STREAMER_H__

//Max amount to read from the socket at once
//The server only sends a little at a time, so doesn't need to be big
const int socketBuff = 512;
//Amount of sound to buffer before playing a segment
const int soundBuff = 65536;
//Number of channels to switch between for seamless buffer switching
const int numChannels = 3;
//Amount to overlap each channel by to improve seamlessness
const int overlap = 1024;

//void startStreamingAudioFallback(char *url, int port, void(*cb)() = 0);
//void stopStreamingAudioFallback();
//void setVolume(int volume);
void initAudio(char *url, int port);
void startStreaming();
void pauseStreaming();
void stopStreaming();
int exitCB(void *sys, void *user);
#endif