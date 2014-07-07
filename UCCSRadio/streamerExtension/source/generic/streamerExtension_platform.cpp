#include "streamerExtension_internal.h"

#include "s3eEdk.h"
s3eResult streamerExtensionInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void streamerExtensionTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult startStreamingAudio_platform()
{
	return S3E_RESULT_FAILURE;
}

s3eResult stopStreamingAudio_platform()
{
	return S3E_RESULT_FAILURE;
}

s3eResult pauseStreamingAudio_platform()
{
	return S3E_RESULT_FAILURE;
}

s3eResult initAudioStream_platform(const char* ip, int port)
{
	return S3E_RESULT_FAILURE;
}
