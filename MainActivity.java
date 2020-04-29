package com.example.pheonixii.sonus;

import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.CheckBox;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    //I made a comment
    ArrayList<String> intervals = new ArrayList<String>();
    MediaPlayer midiFileMediaPlayer;

    /**
     * ONSTOP
     * stop the theme song when we go on to another activity
     */
    protected void onStop(){

        super.onStop();
        midiFileMediaPlayer.stop();
    }

    /**
     * ONCREATE
     * Play the theme song
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // play the theme song
        midiFileMediaPlayer = MediaPlayer.create(this, R.raw.app_sight_singing_theme);
        midiFileMediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                mediaPlayer.reset();
                mediaPlayer.release();
            }
        });
        midiFileMediaPlayer.setLooping(true);
        midiFileMediaPlayer.start();
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * CHECKEDNUM
     * get all the intervals the user checks and put in an array list and return the number selected
     */
    public int checkedNum(){
        // Is the view now checked
        int count = 0;
        CheckBox P1 = findViewById(R.id.P1);
        if(P1.isChecked()) {
            count++;
            intervals.add(P1.getText().toString());
        }
        CheckBox m2 = findViewById(R.id.m2);
        if(m2.isChecked()) {
            count++;
            intervals.add(m2.getText().toString());
        }
        CheckBox M2 = findViewById(R.id.M2);
        if(M2.isChecked()) {
            count++;
            intervals.add(M2.getText().toString());
        }
        CheckBox m3 = findViewById(R.id.m3);
        if(m3.isChecked()) {
            count++;
            intervals.add(m3.getText().toString());
        }
        CheckBox M3 = findViewById(R.id.M3);
        if(M3.isChecked()) {
            count++;
            intervals.add(M3.getText().toString());
        }
        CheckBox P4 = findViewById(R.id.P4);
        if(P4.isChecked()) {
            count++;
            intervals.add(P4.getText().toString());
        }
        CheckBox P5 = findViewById(R.id.P5);
        if(P5.isChecked()) {
            count++;
            intervals.add(P5.getText().toString());
        }
        CheckBox m6 = findViewById(R.id.m6);
        if(m6.isChecked()) {
            count++;
            intervals.add(m6.getText().toString());
        }
        CheckBox M6 = findViewById(R.id.M6);
        if(M6.isChecked()) {
            count++;
            intervals.add(M6.getText().toString());
        }
        CheckBox m7 = findViewById(R.id.m7);
        if(m7.isChecked()) {
            count++;
            intervals.add(m7.getText().toString());
        }
        CheckBox M7 = findViewById(R.id.M7);
        if(M7.isChecked()) {
            count++;
            intervals.add(M7.getText().toString());
        }
        CheckBox P8 = findViewById(R.id.P8);
        if(P8.isChecked()) {
            count++;
            intervals.add(P8.getText().toString());
        }

        return count;
    }

    /**
     * PLAY
     * check to see if they chose at least 3 then send the intervals and start the next activity
     */
    public void play(View view) {
        if(checkedNum()>=3) {
            Intent intent = new Intent(this, GameActivity.class);

            intent.putStringArrayListExtra("interval_list", intervals);
            intent.putExtra("roundNum", 0);

            startActivity(intent);
        }
        else
            Toast.makeText(this, "You require more intervals", Toast.LENGTH_SHORT).show();
    }
}


