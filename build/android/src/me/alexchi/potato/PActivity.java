package me.alexchi.potato;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

public abstract class PActivity extends NativeActivity {
	
	PView m_pView = null;
	
	// load the shared library
	Potato m_pNativePotato = Potato.instance;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d("PActivity", "onCreate");
	}

}
