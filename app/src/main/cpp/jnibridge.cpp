#include <jni.h>
#include <android/log.h>
#include <chrono>

#include <calyx/platform/android/event_defs.h>
#include <calyx/platform/android/system.h>
#include <calyx/platform/android/entry_point.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#define JNI_INFO(...) __android_log_print(ANDROID_LOG_INFO, "adb-jni", __VA_ARGS__)
#define JNI_VERBOSE(...) __android_log_print(ANDROID_LOG_VERBOSE, "adb-jni", __VA_ARGS__)

extern "C" {

// life cycle callbacks
// onCreate - Step 1
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr, jstring filesDir, jstring obbDir, jstring externalFilesDir);
// onCreate - Step 2
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnStart(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnPause(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnResume(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnStop(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnDestroy(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnBackButtonPressed(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_SurfaceCreated(JNIEnv* env, jobject obj, jobject surface);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_SurfaceDestroyed(JNIEnv* env, jobject obj, jobject surface);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged(JNIEnv* env, jobject obj, jboolean hasFocus);

// input callback
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnOrientationUpdate(JNIEnv* env, jobject obj, jfloat azimuth, jfloat pitch, jfloat roll);

};

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr, jstring filesDir, jstring obbDir, jstring externalFilesDir)
{
	JNI_VERBOSE("%s: OnCreate (before creating SurfaceView)", __FUNCTION__);

	const char* filesDirCstr = env->GetStringUTFChars(filesDir, JNI_FALSE);
	const char* obbDirCstr = env->GetStringUTFChars(obbDir, JNI_FALSE);
	const char* externalFilesDirCstr = env->GetStringUTFChars(externalFilesDir, JNI_FALSE);

	android_pre_init(filesDirCstr, obbDirCstr, externalFilesDirCstr);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE("%s: OnCreate (after creating SurfaceView)", __FUNCTION__);
	android_init();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_SurfaceCreated(JNIEnv* env, jobject obj, jobject surface)
{
	JNI_VERBOSE(__FUNCTION__);
	ANativeWindow* wnd = ANativeWindow_fromSurface(env, surface);
	android_created_surface(wnd);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_SurfaceDestroyed(JNIEnv* env, jobject obj, jobject surface)
{
	JNI_VERBOSE(__FUNCTION__);
	android_will_destroy_surface(nullptr);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface)
{
	JNI_VERBOSE(__FUNCTION__);
}

// life cycle
JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnStart(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE(__FUNCTION__);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnPause(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE(__FUNCTION__);
	android_push_pause_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnResume(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE(__FUNCTION__);
	android_push_resume_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnStop(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE(__FUNCTION__);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnDestroy(JNIEnv* env, jobject obj)
{
	JNI_VERBOSE(__FUNCTION__);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnBackButtonPressed(JNIEnv* env, jobject obj)
{
	android_push_key_event(CLX_BACK);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged(JNIEnv* env, jobject obj, jboolean hasFocus)
{
	android_push_focus_event(hasFocus);
}

// input
JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	android_push_touch_down_event((unsigned int)x, (unsigned int)y);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	android_push_touch_up_event((unsigned int)x, (unsigned int)y);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	android_push_touch_move_event((unsigned int)x, (unsigned int)y);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnOrientationUpdate(JNIEnv* env, jobject obj, jfloat azimuth, jfloat pitch, jfloat roll)
{
	android_push_orientation_event((float)azimuth, (float)pitch, (float)roll);
}