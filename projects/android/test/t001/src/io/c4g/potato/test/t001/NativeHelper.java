package io.c4g.potato.test.t001;

import io.c4g.potato.PNativeHelper;

public class NativeHelper extends PNativeHelper {
	
	public static NativeHelper instance = new NativeHelper();

	public String GetAppName() {
		return "t001";
	}

	public void HasReady() {
		//
	}

}
