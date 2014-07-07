/*
 * Internal header for the streamerExtension extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef STREAMEREXTENSION_INTERNAL_H
#define STREAMEREXTENSION_INTERNAL_H

#include "s3eTypes.h"
#include "streamerExtension.h"
#include "streamerExtension_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult streamerExtensionInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult streamerExtensionInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void streamerExtensionTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void streamerExtensionTerminate_platform();
s3eResult startStreamingAudio_platform();

s3eResult stopStreamingAudio_platform();

s3eResult pauseStreamingAudio_platform();

s3eResult initAudioStream_platform(const char* ip, int port);


#endif /* !STREAMEREXTENSION_INTERNAL_H */