package me.alexchi.potato;

import android.app.Activity;
import android.os.Bundle;

public abstract class PActivity extends Activity {
	
	PView m_pView = null;
	
	// load the shared library
	Potato m_pNativePotato = Potato.instance;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	public void runEngine() {
		m_pView = new PView(this);
		setContentView(m_pView);
	}

}
