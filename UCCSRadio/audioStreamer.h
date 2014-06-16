#if !defined(__AUDIO_STREAMER_H__)
#define __AUDIO_STREAMER_H__
void startStreamingAudio(char *ip, int port, void (*cb)() = NULL);
void stopStreamingAudio();
void setVolume(int volume);
#endif