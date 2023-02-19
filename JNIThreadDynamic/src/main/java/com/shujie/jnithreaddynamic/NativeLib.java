package com.shujie.jnithreaddynamic;

public class NativeLib {

    // Used to load the 'jnithreaddynamic' library on application startup.
    static {
        System.loadLibrary("jnithreaddynamic");
    }

    /**
     * A native method that is implemented by the 'jnithreaddynamic' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}