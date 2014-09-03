package me.alexchi.potato;

import android.app.Activity;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.os.Environment;

public abstract class PActivity extends Activity {
	
	PView m_pView = null;
	
	// load the shared library
	Potato m_pNativePotato = Potato.instance;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		String[] paths = this.getAssets().getLocales();
		String ss = paths.toString();
	}
	
	public void runEngine() {
		m_pView = new PView(this);
		setContentView(m_pView);
		
		if (!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
			// TODO Auto-generated catch block
			return;
		}
		try {
			String libr_path = getPackageManager().getApplicationInfo(getPackageName(), 0).dataDir;
			String data_path = Environment.getExternalStorageDirectory().getAbsolutePath() + "/potato";
			//Potato.instance.create(libr_path, data_path, "potato.json");
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
