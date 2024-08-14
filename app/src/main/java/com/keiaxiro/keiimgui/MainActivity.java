package com.keiaxiro.keiimgui;
import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import androidx.viewpager.widget.ViewPager;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("keiimgui");
    }

    public static WindowManager manager;
    public static WindowManager.LayoutParams vParams;

    @SuppressLint("StaticFieldLeak")
    public static View vTouch;
    public static WindowManager windowManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        Settings.canDrawOverlays(this);// Request overlay permission if not granted
// startActivityForResult(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName())), 0);
        start(this);
    }

    public void start(Context context) {
        manager = ((Activity) context).getWindowManager();
        vParams = getAttributes(false);
        WindowManager.LayoutParams wParams = getAttributes(true);

        GLES3JNIView display = new GLES3JNIView(context);
        vTouch = new View(context);
        manager.addView(vTouch, vParams);
        manager.addView(display, wParams);

        View decorView = getWindow().getDecorView();
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN | View.KEEP_SCREEN_ON;
        decorView.setSystemUiVisibility(uiOptions);

        ActionBar actionBar = getActionBar();
        if (actionBar != null) {
            actionBar.hide();
            actionBar.setDisplayShowTitleEnabled(false);
            actionBar.setDisplayShowHomeEnabled(false);
            actionBar.setDisplayShowCustomEnabled(false);
            actionBar.setDisplayUseLogoEnabled(false);
        }

        vTouch.setOnTouchListener(new View.OnTouchListener() {
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();
                switch (action) {
                    case MotionEvent.ACTION_MOVE:
                    case MotionEvent.ACTION_DOWN:
                    case MotionEvent.ACTION_UP:
                        GLES3JNIView.MotionEventClick(action != MotionEvent.ACTION_UP, event.getRawX(), event.getRawY());
                        break;
                    default:
                        break;
                }
                return false;
            }
        });

        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                try {
                    String[] rect = GLES3JNIView.getWindowRect().split("\\|");
                    vParams.x = Integer.parseInt(rect[0]);
                    vParams.y = Integer.parseInt(rect[1]);
                    vParams.width = Integer.parseInt(rect[2]);
                    vParams.height = Integer.parseInt(rect[3]);
                    manager.updateViewLayout(vTouch, vParams);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                handler.postDelayed(this, 20);
            }
        }, 20);
    }

    @SuppressLint("RtlHardcoded")
    public static WindowManager.LayoutParams getAttributes(boolean isWindow) {
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();
        params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT,
                WindowManager.LayoutParams.WRAP_CONTENT,
                0,
                100,
                WindowManager.LayoutParams.TYPE_APPLICATION,
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
                        WindowManager.LayoutParams.FLAG_LAYOUT_IN_OVERSCAN |
                        WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN |
                        WindowManager.LayoutParams.FLAG_SPLIT_TOUCH |
                        WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE |
                        WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE,
                PixelFormat.TRANSPARENT);

        params.flags = WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;

        if (isWindow) {
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }
        params.format = PixelFormat.RGBA_8888;
        params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        params.gravity = Gravity.LEFT | Gravity.TOP;
        params.x = params.y = 0;
        params.width = params.height = isWindow ? WindowManager.LayoutParams.MATCH_PARENT : 0;
        return params;
    }
}

