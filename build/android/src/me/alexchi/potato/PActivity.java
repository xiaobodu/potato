package me.alexchi.potato;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

public abstract class PActivity extends NativeActivity {
	
	public static PActivity instance = null;
	
	public PActivity() {
		PActivity.instance = this;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d("PActivity", "onCreate");
	}

}
