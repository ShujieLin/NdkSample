package com.shujie.ndksample;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    // Used to load the 'ndksample' library on application startup.
    static {
        System.loadLibrary("ndksample");
    }

    static final int number = 100;
    private String name = "testNdk";
    private static int age = 28;

    /*public native String dynamicJavaMethod();*/


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
    //String引用类类型，数组
    public native void testArrayAction(int[] ints, String[] strs);

    public native void changPerson(Person person,String name,int age);

    public native Person newPerson();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        /*test1();*/
        test2();
    }

    private void test1() {
        Log.d(TAG, "jni修改前" + name);
        changName();
        Log.d(TAG, "jni修改后" + name);


        Log.d(TAG, "jni修改前" + age);
        changAge();
        Log.d(TAG, "jni修改后" + age);

        int sum = invokeAddMethod2();
        Log.d(TAG, "native层调用java方法,sum = "+sum);
    }

    /**
     * 通过native函数修改java层的数组
     */
    private void test2() {
        int[] ints = new int[]{1,2,3};
        String[] strings = new String[]{"a","b","c"};

        Log.i(TAG, "test2: before invoke : " + Arrays.toString(ints));
        testArrayAction(ints,strings);
        Log.i(TAG, "test2: after invoke : " + Arrays.toString(ints));


        Person person = new Person(18,"shujie");
        Log.i(TAG, "test2: before invoke" + person.toString());
        changPerson(person,"shujie+1",19);
        Log.i(TAG, "test2: after invoke" + person.toString());

        Log.i(TAG, "test2: newPerson = " + newPerson().toString());
    }
}