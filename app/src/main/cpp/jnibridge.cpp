#include <jni.h>
#include <android/log.h>
#include <chrono>

#include <platform/android/system.h>
#include <platform/android/entry_point.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#define JNI_VERBOSE(...) __android_log_print(ANDROID_LOG_VERBOSE, "adb-jni", __VA_ARGS__)

extern "C" {

// life cycle callbacks
// onCreate - Step 1
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr);
// onCreate - Step 2
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnStart(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnPause(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnResume(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnStop(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnDestroy(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_SurfaceCreated(JNIEnv* env, jobject obj, jobject surface);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged(JNIEnv* env, jobject obj, jboolean hasFocus);

// input callback
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y);
	
};

JNIEXPORT void JNICALL 
Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr)
{
	JNI_VERBOSE("%s: OnCreate (before creating SurfaceView)", __FUNCTION__);
	android_pre_init();
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
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface)
{
	//ANativeWindow* wnd = ANativeWindow_fromSurface(env, surface);
	if (surface) {
		ANativeWindow* wnd = ANativeWindow_fromSurface(env, surface);
		JNI_VERBOSE("%s: 0x%x", __FUNCTION__, (size_t)wnd);
		android_update_surface(wnd);
	} else {
		JNI_VERBOSE("%s: nullptr", __FUNCTION__);
		android_update_surface(nullptr);
	}
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
Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged(JNIEnv* env, jobject obj, jboolean hasFocus)
{
	if (hasFocus) {
		JNI_VERBOSE("Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged: true");
	} else {
		JNI_VERBOSE("Java_com_calyx_mainapp_MainActivity_OnWindowFocusChanged: false");
	}
	android_push_focus_event(hasFocus);
}

// input
JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	//android_push_touch_move_event((unsigned int)x, (unsigned int)y);
	//android_push_touch_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	//android_push_touch_move_event((unsigned int)x, (unsigned int)y);
	//android_push_touch_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	//android_push_touch_move_event((unsigned int)x, (unsigned int)y);
}
