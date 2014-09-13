package io.c4g.potato.test.t001;

import io.c4g.test.t001.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;

public class LaunchActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		this.setContentView(R.layout.main);
		Log.d("LaunchActivity", "onCreate");
		
		Button btn = (Button)findViewById(R.id.btnRun);
		if (null != btn) {
			btn.setOnTouchListener(new OnTouchListener() {
				@Override
				public boolean onTouch(View arg0, MotionEvent arg1) {
					Intent mainIntent = new Intent(LaunchActivity.this, MainActivity.class);
					startActivity(mainIntent);
					// TODO Auto-generated method stub
					return true;
				}}
			);
		}
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		Log.d("LaunchActivity", "onStart");
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		Log.d("LaunchActivity", "onResume");
	}
	
    @Override 
    protected void onPause() {
		Log.d("LaunchActivity", "onPause");
        super.onPause();
    }
    
    @Override 
    protected void onStop() {
		Log.d("LaunchActivity", "onStop");
        super.onStop();
    }
    @Override 
    protected void onDestroy() {
		Log.d("LaunchActivity", "onDestroy");
        super.onDestroy();
    }

}
