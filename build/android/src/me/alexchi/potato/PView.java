package me.alexchi.potato;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;

public class PView extends GLSurfaceView {

	public PView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}
	
	@Override
	public void surfaceCreated(android.view.SurfaceHolder holder) {
		assert holder != null : "[surfaceCreated] holder can't be null";
		holder.setFormat(PixelFormat.TRANSLUCENT);
		//
	}
	
	@Override
	public void surfaceChanged(android.view.SurfaceHolder holder, int format, int w, int h) {
		assert holder != null : "[surfaceChanged] holder can't be null";
		//
	}
	
	@Override
	public void surfaceDestroyed(android.view.SurfaceHolder holder) {
		assert holder != null : "[surfaceDestroyed] holder can't be null";
		//
	}

}
