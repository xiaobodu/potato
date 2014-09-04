package me.alexchi.potato;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

public abstract class PActivity extends NativeActivity {
	
	public static PActivity instance = null;
	
	protected PNativeHelper helper = null;
	
	public PActivity() {
		PActivity.instance = this;

		/// declare the class in dvm
		helper = new PNativeHelper();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d("PActivity", "onCreate");
	}

}
