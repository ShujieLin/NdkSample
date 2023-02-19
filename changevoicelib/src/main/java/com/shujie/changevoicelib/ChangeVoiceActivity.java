package com.shujie.changevoicelib;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.fmod.FMOD;

public class ChangeVoiceActivity extends AppCompatActivity {
    private static final int MODE_NOMAL = 0;
    private static final int MODE_LUOLI = 1;

    static {
        System.loadLibrary("changevoicelib");
    }

    private String path;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_voice);

        path = "file:///android_asset/source.mp3";//path =  "file:///android_asset/derry.mp3";
        FMOD.init(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    public void btn1(View view) {
        voiseChangeNative(MODE_NOMAL, path);
    }

    private native void voiseChangeNative(int modeNomal, String path);

    public void playEndTips(String msg){
        Toast.makeText(this,msg + "" , Toast.LENGTH_SHORT).show();
    }

    public void btn2(View view) {
        voiseChangeNative(MODE_LUOLI, path);
    }
}