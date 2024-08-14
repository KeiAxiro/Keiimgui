package com.keiaxiro.keiimgui;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLES3JNIView extends GLSurfaceView implements GLSurfaceView.Renderer {

    public static byte fontData[];

    public GLES3JNIView(Context context) {
        super(context);
        initial();
    }

    private void initial() {
        // Set OpenGL ES version to 3.0
        setEGLContextClientVersion(3);

        // Configure EGL for RGBA_8888 and depth buffer
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.RGBA_8888);

        // Set the renderer
        setRenderer(this);

        // Request focus and set focusable in touch mode for input responsiveness
        setFocusable(true);
        setFocusableInTouchMode(true);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // Call the step function to perform rendering
        step();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        // Call the resize function to handle surface changes
        resize(width, height);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Call the init function to initialize resources
        init();
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        // Call the imgui_Shutdown function to clean up resources
        imgui_Shutdown();
    }

    // Native methods
    public static native void init();
    public static native void resize(int width, int height);
    public static native void step();
    public static native void imgui_Shutdown();
    public static native void MotionEventClick(boolean down, float PosX, float PosY);
    public static native String getWindowRect();
}

