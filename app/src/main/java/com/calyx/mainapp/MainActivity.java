package com.calyx.mainapp;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.MotionEvent;

public class MainActivity extends Activity implements SurfaceHolder.Callback2 {
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		System.loadLibrary("maincode");
		// native pre-init
		m_AssetManager = getResources().getAssets();
		PreInitialize(m_AssetManager);
		
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
	protected void onPause()
	{
		super.onPause();
	}

	protected void onResume()
	{
		super.onResume();
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
    }
	
	public void surfaceRedrawNeeded(SurfaceHolder holder) {
	}

    public void surfaceDestroyed(SurfaceHolder holder) {
		UpdateSurface(null);
    }

	// -----------------------------------------
	private RelativeLayout						m_MainLayout = null;
	private SurfaceView							m_MainGLView = null;
	private AssetManager						m_AssetManager = null;
	// -----------------------------------------
	
	public native void PreInitialize(AssetManager assetManager);
	public native void Initialize();
	public native void UpdateSurface(Surface surface);

	// native input
	public native void OnTouchDown(float x, float y);
	public native void OnTouchMove(float x, float y);
	public native void OnTouchUp(float x, float y);
}
