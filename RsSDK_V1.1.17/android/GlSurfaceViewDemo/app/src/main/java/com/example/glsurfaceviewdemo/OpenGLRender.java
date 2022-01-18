package com.example.glsurfaceviewdemo;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by czd on 18-3-1.
 */

public class OpenGLRender implements GLSurfaceView.Renderer {

    private long surface_id, preview_id;
    private int width, height;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        surface_id = JniHandler.rs_android_surface_create();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        JniHandler.rs_android_surface_change(surface_id, width, height, preview_id);
        this.width = width;
        this.height = height;
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        JniHandler.rs_android_surface_draw(surface_id, preview_id);
        try {
            Thread.sleep(20);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void SetPreviewID(long preview_id) {
        this.preview_id = preview_id;
    }

    /**
     * @param xLocation
     * @param yLocation
     * @param scaledelta
     * @param mode 0:mouse move, 1:mouse wheel, 2:mouse down, 3:mouse up, 4:mouse double click
     */
    public void setTouchToJni(float xLocation, float yLocation, float scaledelta, int mode) {
        if (preview_id != 0 && width != 0 && height != 0) {
            JniHandler.rs_video_mouse_event(xLocation/width, yLocation/height, scaledelta, mode, preview_id);
        }
    }
}
