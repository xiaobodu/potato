package io.c4g.potato;

public interface IPNativeHelper {

	String GetAppName();
	String GetLibraryPath();
	String GetExternalPath();
	String GetAssetsPath();
	void RequestAssetManager();
	void HasReady();

}
