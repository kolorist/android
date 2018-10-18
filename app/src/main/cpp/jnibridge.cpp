#include <jni.h>
#include <android/log.h>
#include <chrono>

#include <platform/android/system.h>
#include <platform/android/entry_point.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr);	// onCreate step 1
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj);						// onCreate step 2
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface);
	// input
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL 
Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr)
{
	android_pre_init();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj)
{
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface)
{
	static bool init = false;
	if (!init) {
		ANativeWindow* wnd = ANativeWindow_fromSurface(env, surface);
		android_update_surface(wnd);
		android_init();
		init = true;
	}
}

// input
JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{

}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{

}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	android_push_touch_move_event((unsigned int)x, (unsigned int)y);
}
