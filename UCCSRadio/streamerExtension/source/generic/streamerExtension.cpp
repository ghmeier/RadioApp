/*
Generic implementation of the streamerExtension extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "streamerExtension_internal.h"
s3eResult streamerExtensionInit()
{
    //Add any generic initialisation code here
    return streamerExtensionInit_platform();
}

void streamerExtensionTerminate()
{
    //Add any generic termination code here
    streamerExtensionTerminate_platform();
}

s3eResult startStreamingAudio()
{
	return startStreamingAudio_platform();
}

s3eResult stopStreamingAudio()
{
	return stopStreamingAudio_platform();
}

s3eResult pauseStreamingAudio()
{
	return pauseStreamingAudio_platform();
}

s3eResult initAudioStream(const char* ip, int port)
{
	return initAudioStream_platform(ip, port);
}
