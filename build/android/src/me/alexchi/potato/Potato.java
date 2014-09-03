package me.alexchi.potato;

public class Potato {
	
	static {
		System.loadLibrary("potato");
	}
	
	public static Potato instance = new Potato();
	
	private Potato() {
		//
	}
	
	public native void create(String sLibrPath, String sDataPath, String sFile);
	public native void destroy();

	public class Render {
		public native void start();
		public native void resize(int iWidth, int iHeight);
		public native void stop();
	}
	public Render render = new Render();

}
