package io.c4g.potato.demo;

import android.os.Environment;
import io.c4g.potato.PNativeHelper;

public class NativeHelper extends PNativeHelper {
	
	public static NativeHelper instance = new NativeHelper();

	public String GetAppName() {
		return "demo";
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

	public void HasReady() {
		//
	}

}
