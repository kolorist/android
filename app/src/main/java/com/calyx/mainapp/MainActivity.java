package com.calyx.mainapp;

import android.app.Activity;
import android.util.Log;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.content.Context;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.MotionEvent;
import java.io.File;

public class MainActivity extends Activity implements SurfaceHolder.Callback2 {

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		System.loadLibrary("lucent");
		// get essential directories
		m_Context = getApplicationContext();
		File filesDir = m_Context.getFilesDir();
		File obbDir = m_Context.getObbDir();
		File externalFilesDir = m_Context.getExternalFilesDir(null);

		// native pre-init
		m_AssetManager = getResources().getAssets();
		PreInitialize(m_AssetManager, filesDir.getPath(), obbDir.getPath(), externalFilesDir.getPath());

		m_MainLayout = new RelativeLayout(this);
		m_MainGLView = new SurfaceView(this);

		m_MainGLView.setEnabled(true);
		m_MainGLView.setFocusable(true);
		m_MainGLView.setFocusableInTouchMode(true);

		m_MainGLView.getHolder().addCallback(this);
		m_MainLayout.addView(m_MainGLView);
		setContentView(m_MainLayout);

		// native init
		Initialize();
	}

	// life-cycle
	@Override
	protected void onStart()
	{
		super.onStart();

		OnStart();
	}

	@Override
	protected void onPause()
	{
		super.onPause();

		OnPause();
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		OnResume();
	}

	@Override
	protected void onStop()
	{
		super.onStop();

		OnStop();
	}

	@Override
	protected void onDestroy()
	{
		super.onDestroy();

		OnDestroy();
	}

	// surface

	@Override
	public void onWindowFocusChanged(boolean hasFocus)
	{
		super.onWindowFocusChanged(hasFocus);

		OnWindowFocusChanged(hasFocus);
	}

	// input
	@Override
	public boolean onTouchEvent(final MotionEvent ev)
	{
		float x = ev.getX();
		float y = ev.getY();

		switch (ev.getAction()) {
			case MotionEvent.ACTION_DOWN:
				{
					OnTouchDown(x, y);
					break;
				}
			case MotionEvent.ACTION_MOVE:
				{
					OnTouchMove(x, y);
					break;
				}
			case MotionEvent.ACTION_UP:
				{
					OnTouchUp(x, y);
					break;
				}
			default:
				break;
		}

		return super.onTouchEvent(ev);
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
		UpdateSurface(holder.getSurface());
	}

	public void surfaceCreated(SurfaceHolder holder) {
		SurfaceCreated(holder.getSurface());
	}

	public void surfaceRedrawNeeded(SurfaceHolder holder) {
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		SurfaceDestroyed(holder.getSurface());
	}

	// -----------------------------------------
	private RelativeLayout						m_MainLayout = null;
	private SurfaceView							m_MainGLView = null;
	private Context								m_Context = null;
	private AssetManager						m_AssetManager = null;
	// -----------------------------------------

	public native void PreInitialize(AssetManager assetManager, String filesDir, String obbDir, String externalFilesDir);
	public native void Initialize();
	public native void SurfaceCreated(Surface surface);
	public native void SurfaceDestroyed(Surface surface);
	public native void UpdateSurface(Surface surface);

	// life cycle
	public native void OnStart();
	public native void OnPause();
	public native void OnResume();
	public native void OnStop();
	public native void OnDestroy();
	public native void OnWindowFocusChanged(boolean hasFocus);

	// native input
	public native void OnTouchDown(float x, float y);
	public native void OnTouchMove(float x, float y);
	public native void OnTouchUp(float x, float y);
}
