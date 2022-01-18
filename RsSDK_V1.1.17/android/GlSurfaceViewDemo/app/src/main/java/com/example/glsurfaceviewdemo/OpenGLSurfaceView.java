package com.example.glsurfaceviewdemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.FloatMath;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.SurfaceHolder;
import android.view.ViewGroup;

/**
 * Created by czd on 18-3-1.
 */

public class OpenGLSurfaceView extends GLSurfaceView implements SurfaceHolder.Callback {

    private OpenGLRender mRender;
    public GestureDetector mGestureDetector;
    public ScaleGestureDetector mScaleDetector;

    private double thirdClick = 0;
    private float oldDist;
    private float xLocation;
    private float yLocation;
    private float xDelta;
    private float yDelta;
    private float scaledelta;
    private float previousX, previousY;
    private int mode;


    public OpenGLSurfaceView(Context context) {
        this(context, null);
    }

    public OpenGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public void init() {
        setEGLContextClientVersion(3);
        mRender = new OpenGLRender();
        setRenderer(mRender);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        mGestureDetector = new GestureDetector(getContext(), new ViewOnTouchListener());
    }

    public void SetPreviewID(long preview_id) {
        if (mRender != null) {
            mRender.SetPreviewID(preview_id);
        }
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent event) {
        final int Action = event.getActionMasked();
        gestureDetector(event);
        return true;
    }

    private boolean gestureDetector(MotionEvent event) {
        if(mGestureDetector != null) {
            mGestureDetector.onTouchEvent(event);
            mGestureDetector.setIsLongpressEnabled(true);
        }
        switch (event.getAction() & MotionEvent.ACTION_MASK) {
            case MotionEvent.ACTION_DOWN:
                break;
            case MotionEvent.ACTION_UP:
                thirdClick = System.currentTimeMillis();
                mode = 3;
                handleTouchToJni();
                scaledelta = 0;
                break;
            case MotionEvent.ACTION_POINTER_UP:
                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                oldDist = spacing(event);
                break;

            case MotionEvent.ACTION_MOVE:
                if (event.getPointerCount() >= 2) {
                    mode = 1;
                    float newDist = spacing(event);
                    if (newDist > oldDist + 10) {
                        scaledelta = newDist / oldDist;
                        oldDist = newDist;
                    }
                    if (newDist < oldDist - 10) {
                        scaledelta = newDist / oldDist;
                        oldDist = newDist;
                    }
                    handleTouchToJni();
                }
                break;
            default:
                break;

        }
        return true;
    }


    private float spacing(MotionEvent event) {
        float x = event.getX(0) - event.getX(1);
        float y = event.getY(0) - event.getY(1);
        return (float) Math.sqrt(x * x + y * y);
    }

    public void handleTouchToJni() {
        mRender.setTouchToJni(xLocation, yLocation, scaledelta, mode);
    }

    class ViewOnTouchListener extends GestureDetector.SimpleOnGestureListener {

        @Override
        public boolean onDown(MotionEvent e) {
            mode = 2;
            previousX = e.getX();
            previousY = e.getY();
            xLocation = previousX;
            yLocation = previousY;
            handleTouchToJni();
            return true;
        }


        @Override
        public void onShowPress(MotionEvent e) {

        }

        @Override
        public boolean onSingleTapUp(MotionEvent e) {
            return false;
        }

        @Override
        public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
            xLocation = e2.getX();
            yLocation = e2.getY();
            mode = 0;
            handleTouchToJni();
            return true;
        }

        @Override
        public void onLongPress(MotionEvent e) {

        }

        @Override
        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
            return false;
        }

        @Override
        public boolean onDoubleTap(MotionEvent e) {
            mGestureDetector.setIsLongpressEnabled(false);
            xLocation = e.getX();
            yLocation = e.getY();
            mode = 4;
            handleTouchToJni();
            return true;
        }
    }

}
