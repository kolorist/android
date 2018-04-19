#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>

// #include <pthread.h>
// #include <android_utils.h>
// #include <platform.h>

// int android_main(int* argc, char** argv);
// void* android_main_thread(void*) {
	// android_main(nullptr, nullptr);
	// pthread_exit(nullptr);
// }

extern "C" {
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface);
	// input
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL 
Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr)
{
	// native_console_log("PreInitialize");
	// g_RenderWindow.pm_NativeWindow = nullptr;
	// g_RenderWindow.pm_IsGameThreadInit = false;
	
	// init_event_queue();
	// set_asset_manager(AAssetManager_fromJava(env, assetMgr));
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj)
{
	// native_console_log("Initialize");
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_UpdateSurface(JNIEnv* env, jobject obj, jobject surface)
{
	// native_console_log("UpdateSurface");
	// if (surface != 0) {
		// g_RenderWindow.pm_NativeWindow = ANativeWindow_fromSurface(env, surface);
		// if (!g_RenderWindow.pm_IsGameThreadInit) {
			// native_console_log("Creating main thread");
			// pthread_t t;
			// pthread_create(&t, NULL, android_main_thread, NULL);
			// g_RenderWindow.pm_IsGameThreadInit = true;
			// native_console_log("Done");
		// }
	// } else {
		// ANativeWindow_release(g_NativeWindow);
	// }
}

// input
JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchDown(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchDown @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchDown, mX, mY);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchUp @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchUp, mX, mY);
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchMove @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchMove, mX, mY);
}
