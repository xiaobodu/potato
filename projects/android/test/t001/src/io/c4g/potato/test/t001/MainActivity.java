package io.c4g.potato.test.t001;

import io.c4g.potato.IPNativeHelper;
import io.c4g.potato.PActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends PActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		//this.setContentView(R.layout.main);
		Log.d("MainActivity", "onCreate");
		//this.addContentView(LayoutInflater.from(this).inflate(R.layout.main, null), null);
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		View curr = this.getCurrentFocus();
		Log.d("MainActivity", "onStart " + curr);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		View curr = this.getCurrentFocus();
		Log.d("MainActivity", "onResume " + curr);
	}
	
    @Override 
    protected void onPause() {
		View curr = this.getCurrentFocus();
		Log.d("MainActivity", "onPause " + curr);
        super.onPause();
    }
    
    @Override 
    protected void onStop() {
		Log.d("MainActivity", "onStop");
        super.onStop();
    }
    @Override 
    protected void onDestroy() {
		Log.d("MainActivity", "onDestroy");
        super.onDestroy();
    }

	@Override
	public IPNativeHelper getHelper() {
		return NativeHelper.instance;
	}

}
