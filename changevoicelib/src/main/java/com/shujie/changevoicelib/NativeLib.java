package com.shujie.changevoicelib;

public class NativeLib {

    // Used to load the 'changevoicelib' library on application startup.
    static {
        System.loadLibrary("changevoicelib");
    }

    /**
     * A native method that is implemented by the 'changevoicelib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}