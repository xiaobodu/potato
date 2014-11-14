package io.c4g.potato.test;

import io.c4g.potato.PNativeHelper;

public class NativeHelper extends PNativeHelper {
	
	public static NativeHelper instance = new NativeHelper();

	public String GetAppName() {
		return "t001";
	}
	
	public String GetAssetsPath() {
		return "data/";
	}

	public void HasReady() {
		//
	}

}
