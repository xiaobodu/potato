package io.c4g.potato.test.t001;

import io.c4g.potato.IPNativeHelper;
import io.c4g.potato.PActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends PActivity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Log.d("MainActivity", "onCreate");
	}

	@Override
	public IPNativeHelper getHelper() {
		return NativeHelper.instance;
	}

}
