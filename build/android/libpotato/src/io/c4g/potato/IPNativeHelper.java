package io.c4g.potato;

import android.content.res.AssetManager;

public interface IPNativeHelper {

	String GetAppName();
	String GetLibraryPath();
	String GetExternalPath();
	AssetManager GetAssetManager();
	void HasReady();

}
