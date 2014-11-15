package io.c4g.potato;

import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;

public abstract class PNativeHelper implements IPNativeHelper {
	
	public PNativeHelper() {
		;
	}

	public String GetLibraryPath() {
		assert null != PActivity.instance : "the instance of PActivity is null";
		try {
			return PActivity.instance.getPackageManager().getApplicationInfo(PActivity.instance.getPackageName(), 0).dataDir + "/lib";
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return "";
	}

	public AssetManager GetAssetManager() {
		if (PActivity.instance == null) return null;
		return PActivity.instance.getAssets();
	}

}
