package io.c4g.potato;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

public abstract class PActivity extends NativeActivity implements IPActivity {
	
	public static PActivity instance = null;
	
	@SuppressWarnings("unused")
	private IPNativeHelper m_pHelper = null;
	
	public PActivity() {
		PActivity.instance = this;
		
		m_pHelper = getHelper();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d("PActivity", "onCreate");
	}

}
