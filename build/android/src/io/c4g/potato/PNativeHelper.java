package io.c4g.potato;

import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Environment;

public abstract class PNativeHelper implements IPNativeHelper {
	
	public PNativeHelper() {
		;
	}

	public String GetLibraryPath() {
		assert null != PActivity.instance : "the instance of PActivity is null";
		try {
			return PActivity.instance.getPackageManager().getApplicationInfo(PActivity.instance.getPackageName(), 0).dataDir;
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return "";
	}

	public String GetExternalPath() {
		/*try {
			Thread.sleep(15000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
		return Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + GetAppName();
	}

}
