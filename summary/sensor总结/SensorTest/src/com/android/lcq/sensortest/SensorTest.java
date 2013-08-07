package com.android.lcq.sensortest;

import android.app.Activity;
import android.os.Bundle;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.widget.TextView;
import android.graphics.Color;

public class SensorTest extends Activity {
	/** Called when the activity is first created. */
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	private Sensor mGyroscape;
	private Sensor mMagnetic;
	private Sensor mOrientation;
	private Sensor mLight;
	private Sensor mProximity;
	private SensorTestListener mSensorTestListener;
	private TextView tvAcc;
	private TextView tvMagnetic;
	private TextView tvGyro;
	private TextView tvOrien;
	private TextView tvLight;
	private TextView tvProximity;
	private String disp;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		
		mAccelerometer = mSensorManager
				.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mGyroscape = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
		mMagnetic = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		mOrientation = mSensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
		mLight = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
		mProximity = mSensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY);

		mSensorTestListener = new SensorTestListener();

		tvAcc = (TextView) findViewById(R.id.textView2);
		tvMagnetic = (TextView) findViewById(R.id.textView4);
		tvGyro = (TextView) findViewById(R.id.textView6);
		tvOrien = (TextView) findViewById(R.id.textView8);
		tvLight = (TextView) findViewById(R.id.textView10);
		tvProximity = (TextView) findViewById(R.id.textView12);
	}

	@Override
	protected void onResume() {
		super.onResume();
//		mSensorManager.registerListener(mSensorTestListener, mAccelerometer,
//				SensorManager.SENSOR_DELAY_FASTEST);
//		mSensorManager.registerListener(mSensorTestListener, mGyroscape,
//				SensorManager.SENSOR_DELAY_FASTEST);
//		mSensorManager.registerListener(mSensorTestListener, mMagnetic,
//				SensorManager.SENSOR_DELAY_FASTEST);
//		mSensorManager.registerListener(mSensorTestListener, mOrientation,
//				SensorManager.SENSOR_DELAY_FASTEST);
//		mSensorManager.registerListener(mSensorTestListener, mLight,
//				SensorManager.SENSOR_DELAY_FASTEST);
//		mSensorManager.registerListener(mSensorTestListener, mProximity,
//				SensorManager.SENSOR_DELAY_FASTEST);
		//
		 mSensorManager.registerListener(mSensorTestListener, mAccelerometer,
		 SensorManager.SENSOR_DELAY_FASTEST);
		 mSensorManager.registerListener(mSensorTestListener, mGyroscape,
		 SensorManager.SENSOR_DELAY_FASTEST);
		 mSensorManager.registerListener(mSensorTestListener, mMagnetic,
		 SensorManager.SENSOR_DELAY_FASTEST);
		 mSensorManager.registerListener(mSensorTestListener, mOrientation,
		 SensorManager.SENSOR_DELAY_NORMAL);
		 mSensorManager.registerListener(mSensorTestListener, mLight,
		 SensorManager.SENSOR_DELAY_NORMAL);
		 mSensorManager.registerListener(mSensorTestListener, mProximity,
		 SensorManager.SENSOR_DELAY_NORMAL);
	}

	@Override
	protected void onPause() {
		super.onPause();
		mSensorManager.unregisterListener(mSensorTestListener);
	}

	private class SensorTestListener implements SensorEventListener {
		public void onAccuracyChanged(Sensor sensor, int accuracy) {

		}

		public void onSensorChanged(SensorEvent event) {
			// System.out.println("onSensorChanged\n");
			if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
				disp = "X: " + String.format("%1.4f", event.values[0])
						+ "    Y: " + String.format("%1.4f", event.values[1])
						+ "    Z: " + String.format("%1.4f", event.values[2]);
				tvAcc.setText(disp);
				System.out.println("TYPE_ACCELEROMETER\n");
			} else if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
				disp = "X: " + String.format("%1.4f", event.values[0])
						+ "    Y: " + String.format("%1.4f", event.values[1])
						+ "    Z: " + String.format("%1.4f", event.values[2]);
				tvGyro.setText(disp);
				System.out.println("TYPE_GYROSCOPE\n");
			} else if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
				disp = "X: " + String.format("%1.4f", event.values[0])
						+ "    Y: " + String.format("%1.4f", event.values[1])
						+ "    Z: " + String.format("%1.4f", event.values[2]);
				tvMagnetic.setText(disp);
				System.out.println("TYPE_MAGNETIC_FIELD\n");
			} else if (event.sensor.getType() == Sensor.TYPE_ORIENTATION) {
				disp = "Azimuth: " + String.format("%1.1f", event.values[0])
						+ "    Pitch: "
						+ String.format("%1.1f", event.values[1])
						+ "    Roll: "
						+ String.format("%1.1f", event.values[2]);
				tvOrien.setText(disp);
				System.out.println("TYPE_ORIENTATION\n");
			} else if (event.sensor.getType() == Sensor.TYPE_LIGHT) {
				disp = "Light Lux: " + String.format("%1.2f", event.values[0]);
				tvLight.setText(disp);
				System.out.println("TYPE_LIGHT\n");
			} else if (event.sensor.getType() == Sensor.TYPE_PROXIMITY) {
				disp = "Distance: " + String.format("%1.2f", event.values[0]);
				tvProximity.setText(disp);
				System.out.println("TYPE_PROXIMITY\n");
			}
		}
	}
}