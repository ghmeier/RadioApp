/*
 * iphone-specific implementation of the streamerExtension extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "streamerExtension_internal.h"

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
    return S3E_RESULT_ERROR;
}

s3eResult stopStreamingAudio_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult pauseStreamingAudio_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult initAudioStream_platform(const char* ip, int port)
{
    return S3E_RESULT_ERROR;
}
