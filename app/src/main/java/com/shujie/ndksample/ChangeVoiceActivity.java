package com.shujie.ndksample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class ChangeVoiceActivity extends AppCompatActivity {
    static {
        System.loadLibrary("ndksample");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_voice);
        
    }
}