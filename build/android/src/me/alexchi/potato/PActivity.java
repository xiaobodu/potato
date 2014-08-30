package me.alexchi.potato;

import android.app.Activity;
import android.os.Bundle;

public abstract class PActivity extends Activity {
	
	PView m_pView = null;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		m_pView = new PView(this);
		setContentView(m_pView);
		
		Potato.instance.create();
	}
	
	public void toDebug() {
		Potato.instance.create();
	}

}
