package com.shujie.ndksample;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    // Used to load the 'ndksample' library on application startup.
    static {
        System.loadLibrary("ndksample");
    }

    static final int number = 100;
    private String name = "testNdk";
    private static int age = 28;

    /**
     * 通过jni修改java的变量
     */
    private native void changName();

    /**
     * 通过jni修改java层的静态变量
     */
    private native void changAge();

    /*交互JNI*/
    /**
     * 用于给native层调用
     */
    public int addMethod(int num1,int num2){
        return num1 + num2;
    }

    /**
     * 提供给jni层
     */
    public native void invokeAddMethod();

    public native int invokeAddMethod2();
    public native String testJNI();

    public static native String testStaticJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG, "jni修改前" + name);
        changName();
        Log.d(TAG, "jni修改后" + name);


        Log.d(TAG, "jni修改前" + age);
        changAge();
        Log.d(TAG, "jni修改后" + age);

        int sum = invokeAddMethod2();
        Log.d(TAG, "native层调用java方法,sum = "+sum);
    }
}