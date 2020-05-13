package com.calyx.mainapp;

import android.app.Activity;
import android.util.Log;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.MotionEvent;
import java.io.File;

public class MainActivity extends Activity implements SurfaceHolder.Callback2
{
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		System.loadLibrary("insigne_dev");
		// get essential directories
		m_Context = getApplicationContext();
		File filesDir = m_Context.getFilesDir();
		File obbDir = m_Context.getObbDir();
		File externalFilesDir = m_Context.getExternalFilesDir(null);

		// hardware init
		m_SensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
		m_AccelerometerSensor = m_SensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		m_Gravity = new float[] { 0.0f, 0.0f, 0.0f };
		m_AccelerometerListener = new SensorEventListener()
		{
			@Override
			public void onSensorChanged(final SensorEvent ev)
			{
				m_Gravity[0] = ev.values[0];
				m_Gravity[1] = ev.values[1];
				m_Gravity[2] = ev.values[2];
				onOrientationUpdated();
			}

			@Override
			public void onAccuracyChanged(final Sensor sensor, final int accuracy)
			{
				// nothing
			}
		};
		m_MagneticFieldSensor = m_SensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		m_Geomagnetic = new float[] { 0.0f, 0.0f, 0.0f };
		m_MagneticFieldListener = new SensorEventListener()
		{
			@Override
			public void onSensorChanged(final SensorEvent ev)
			{
				m_Geomagnetic[0] = ev.values[0];
				m_Geomagnetic[1] = ev.values[1];
				m_Geomagnetic[2] = ev.values[2];
				onOrientationUpdated();
			}

			@Override
			public void onAccuracyChanged(final Sensor sensor, final int accuracy)
			{
				// nothing
			}
		};
		m_LastOrientation = new float[] { 0.0f, 0.0f, 0.0f };

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

		m_SensorManager.unregisterListener(m_MagneticFieldListener);
		m_SensorManager.unregisterListener(m_AccelerometerListener);
		OnPause();
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		m_SensorManager.registerListener(m_AccelerometerListener, m_AccelerometerSensor, SensorManager.SENSOR_DELAY_GAME);
		m_SensorManager.registerListener(m_MagneticFieldListener, m_MagneticFieldSensor, SensorManager.SENSOR_DELAY_GAME);
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

	@Override
	public void onBackPressed()
	{
		OnBackButtonPressed();
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
		int pointerIndex = ev.getActionIndex();
		int pointerId = ev.getPointerId(pointerIndex);
		int maskedAction = ev.getActionMasked();
		switch (maskedAction)
		{
			case MotionEvent.ACTION_DOWN:
			case MotionEvent.ACTION_POINTER_DOWN:
			{
				float x = ev.getX(pointerIndex);
				float y = ev.getY(pointerIndex);
				OnTouchDown(pointerId, x, y);
				break;
			}
			case MotionEvent.ACTION_MOVE:
			{
				// a pointer moved, we have to send everyone back
				for (int i = 0; i < ev.getPointerCount(); i++)
				{
					int movePointerId = ev.getPointerId(i);
					float x = ev.getX(i);
					float y = ev.getY(i);
					OnTouchMove(movePointerId, x, y);
				}
				break;
			}
			case MotionEvent.ACTION_UP:
			case MotionEvent.ACTION_POINTER_UP:
			case MotionEvent.ACTION_CANCEL:
			{
				float x = ev.getX(pointerIndex);
				float y = ev.getY(pointerIndex);
				OnTouchUp(pointerId, x, y);
				break;
			}
			default:
				break;
		}

		return true;
	}

	public void onOrientationUpdated()
	{
		float[] R = new float[9];
		SensorManager.getRotationMatrix(R, null, m_Gravity, m_Geomagnetic);
		float[] orient = new float[3];
		SensorManager.getOrientation(R, orient);
		final float k_pi = 3.141592653589793f;
		orient[0] = orient[0] * 180.0f / k_pi; // azimuth
		orient[1] = orient[1] * 180.0f / k_pi; // pitch
		orient[2] = orient[2] * 180.0f / k_pi; // roll

		float d0 = orient[0] - m_LastOrientation[0];
		float d1 = orient[1] - m_LastOrientation[1];
		float d2 = orient[2] - m_LastOrientation[2];
		final float k_epsilon = 2.0f;
		float sqrD = d0 * d0 + d1 * d1 + d2 * d2;
		if (sqrD > k_epsilon * k_epsilon)
		{
			m_LastOrientation[0] = orient[0];
			m_LastOrientation[1] = orient[1];
			m_LastOrientation[2] = orient[2];
			OnOrientationUpdate(orient[0], orient[1], orient[2]);
		}
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

	private SensorManager						m_SensorManager = null;
	private Sensor								m_AccelerometerSensor = null;
	private SensorEventListener					m_AccelerometerListener = null;
	private float								m_Gravity[];
	private Sensor								m_MagneticFieldSensor = null;
	private SensorEventListener					m_MagneticFieldListener = null;
	private float								m_Geomagnetic[];
	private float								m_LastOrientation[];
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
	public native void OnBackButtonPressed();
	public native void OnWindowFocusChanged(boolean hasFocus);

	// native input
	public native void OnTouchDown(int pid, float x, float y);
	public native void OnTouchMove(int pid, float x, float y);
	public native void OnTouchUp(int pid, float x, float y);
	public native void OnOrientationUpdate(float azimuth, float pitch, float roll);
}
