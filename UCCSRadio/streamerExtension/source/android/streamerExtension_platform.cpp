/*
 * android-specific implementation of the streamerExtension extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "streamerExtension_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_startStreamingAudio;
static jmethodID g_stopStreamingAudio;
static jmethodID g_pauseStreamingAudio;
static jmethodID g_initAudioStream;

s3eResult streamerExtensionInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("streamerExtension");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_startStreamingAudio = env->GetMethodID(cls, "startStreamingAudio", "()I");
    if (!g_startStreamingAudio)
        goto fail;

    g_stopStreamingAudio = env->GetMethodID(cls, "stopStreamingAudio", "()I");
    if (!g_stopStreamingAudio)
        goto fail;

    g_pauseStreamingAudio = env->GetMethodID(cls, "pauseStreamingAudio", "()I");
    if (!g_pauseStreamingAudio)
        goto fail;

    g_initAudioStream = env->GetMethodID(cls, "initAudioStream", "(Ljava/lang/String;I)I");
    if (!g_initAudioStream)
        goto fail;



    IwTrace(STREAMEREXTENSION, ("STREAMEREXTENSION init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(streamerExtension, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void streamerExtensionTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult startStreamingAudio_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_startStreamingAudio);
}

s3eResult stopStreamingAudio_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_stopStreamingAudio);
}

s3eResult pauseStreamingAudio_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_pauseStreamingAudio);
}

s3eResult initAudioStream_platform(const char* ip, int port)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring ip_jstr = env->NewStringUTF(ip);
    return (s3eResult)env->CallIntMethod(g_Obj, g_initAudioStream, ip_jstr, port);
}
