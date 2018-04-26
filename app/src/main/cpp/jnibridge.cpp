#include <jni.h>
#include <android/log.h>
#include <chrono>

#include <platform/android/system.h>
#include <platform/android/entry_point.h>
// #include <android/asset_manager_jni.h>
#include <android/native_window.h>
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

void force_lhs(int* s, int n)
{
	*s = 0;
	for (int i = 0; i < n; i++) {
		*s += i;
	}
}

void no_lhs(int *s, int n)
{
	int is = 0;
	for (int i = 0; i < n; i++) {
		is += i;
	}
	*s = is;
}

JNIEXPORT void JNICALL 
Java_com_calyx_mainapp_MainActivity_PreInitialize(JNIEnv* env, jobject obj, jobject assetMgr)
{
	/*
	__android_log_print(ANDROID_LOG_INFO, "native_log", "PreInitialize");

	int sum = 0;
	
	for (int i = 0; i < 50; i++) {
		auto start = std::chrono::system_clock::now();
		force_lhs(&sum, 10000000);
		auto end = std::chrono::system_clock::now();
		std::chrono::microseconds elapsed_ms = end - start;
		__android_log_print(ANDROID_LOG_INFO, "native_log", "time 1 = %lld microsec", elapsed_ms.count());
	}

	for (int i = 0; i < 50; i++) {
		auto start = std::chrono::system_clock::now();
		no_lhs(&sum, 10000000);
		auto end = std::chrono::system_clock::now();
		std::chrono::microseconds elapsed_ms = end - start;
		__android_log_print(ANDROID_LOG_INFO, "native_log", "time 2 = %lld microsec", elapsed_ms.count());
	}
	*/
	
	// native_console_log("PreInitialize");
	// g_RenderWindow.pm_NativeWindow = nullptr;
	// g_RenderWindow.pm_IsGameThreadInit = false;
	
	// init_event_queue();
	// set_asset_manager(AAssetManager_fromJava(env, assetMgr));
	android_pre_init();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_Initialize(JNIEnv* env, jobject obj)
{
	// native_console_log("Initialize");
	//android_init();
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
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchDown @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchDown, mX, mY);
	android_push_touch_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchUp(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchUp @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchUp, mX, mY);
	android_push_touch_event();
}

JNIEXPORT void JNICALL
Java_com_calyx_mainapp_MainActivity_OnTouchMove(JNIEnv* env, jobject obj, jfloat x, jfloat y)
{
	// float mX = x;
	// float mY = y;
	// native_console_logf("TouchMove @ %f - %f", mX, mY);
	// queue_touch_event(TouchEventType::TouchMove, mX, mY);
	android_push_touch_event();
}
