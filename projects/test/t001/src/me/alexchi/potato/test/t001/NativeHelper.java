package me.alexchi.potato.test.t001;

import me.alexchi.potato.PNativeHelper;

public class NativeHelper extends PNativeHelper {
	
	public static NativeHelper instance = new NativeHelper();

	public String GetAppName() {
		return "t001";
	}

}
