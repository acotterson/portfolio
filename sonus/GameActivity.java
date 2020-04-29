package com.example.pheonixii.sonus;

import android.content.Intent;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Random;


public class GameActivity extends AppCompatActivity {
    static final String SAVE_FILE = "";

    VerifyNotes verifyNotes = new VerifyNotes();

    // ImageViews to remember which view was used last in order to delete them later.

    private int submits = 0;
    private boolean digression = false;
    private ImageView noteB = null;
    private ImageView sharpB = null;
    private ImageView noteU = null;
    private ImageView sharpU = null;
    private ImageView noteR = null;
    private ImageView sharpR = null;
    public ImageMap imageMap = new ImageMap();

    int highestNote = 82;
    private int roundNum = 0;

    Spinner spinner;

    boolean feedBack;
    boolean hasSubmitted;


    /**
     * ON CREATE
     * - Sets up the view spinner
     * - Sets intervals with data from last activity
     * - Roundnum = 0
     * - Calls startRound
     *
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);

        //initialize intent
        Intent intent = getIntent();

        //set intervals
        verifyNotes.setIntervals(intent.getStringArrayListExtra("interval_list"));

        //set empty spinner to view spinner
        spinner = findViewById(R.id.intervals_spinner);
        verifyNotes.setSpinner(spinner);

        //preparing adapter for spinner
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, getIntervals());

        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        //add adapter to spinner
        spinner.setAdapter(adapter);

        roundNum = 0;

        startRound();
    }

    /**
     * START ROUND
     * - Sets a new random interval, base note and test note
     * - Displays base note
     */
    public void startRound() {
        verifyNotes.setInterval(verifyNotes.randomInterval());
        randomBaseNote(); //has to go before the test note
        intervalTestNote();
        hasSubmitted = false;

        SeekBar noteSelect = findViewById(R.id.noteSelect);

        noteSelect.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                displayNote(getUserNote(), "User");
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        RadioGroup sharpSelect = findViewById(R.id.sharpSelect);

        sharpSelect.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                displayNote(getUserNote(), "User");
            }
        });
        displayNote(verifyNotes.getBaseNoteKey(), "Base");
        soundOff();
    }

    /**
     * GO HOME
     *
     * @param view
     */
    public void goHome(View view) {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }

    /**
     * GET INTERVALS
     * returns the arraylist of intervals
     */
    public ArrayList<String> getIntervals() {
        return verifyNotes.getIntervals();
    }

    /**
     * SUBMIT
     * - Verifies note and sets hasSubmitted to true
     *
     * @param view
     */
    public void submit(View view) {

        feedBack = false;
        if (!hasSubmitted) {
            verifyNotes.verifyAnswer();
            hasSubmitted = true;
            if (verifyNotes.verifyNote()) {
                feedBack = true;
            } else {
                displayNote(verifyNotes.getTestNoteKey(), "Correct");
            }
            noteFeedback(feedBack);
            submits++;
        }
        Toast.makeText(this, verifyNotes.getInterval(), Toast.LENGTH_SHORT).show();
    }

    /**
     * NEXT
     * - sets the correct note to invisible
     * - sets the red X or green checkmark to invisible
     * - add 1 to round number
     * - sends to stat page if the user has played 10 rounds
     */
    public void next(View view) {

        if (!hasSubmitted) {
            Toast.makeText(this, "You have to submit first!", Toast.LENGTH_SHORT).show();
            return;
        }
        roundNum++;

        // change spinner color to black if it was changed green
        spinner.setEnabled(true);
        if (verifyNotes.getIntervals().size() != 1) {

            if (verifyNotes.getIntervals().indexOf(verifyNotes.getInterval()) == getIntervals().indexOf(getIntervals().get(0)))
                spinner.setSelection(verifyNotes.getIntervals().indexOf(verifyNotes.getIntervals().get(1)));
            else
                spinner.setSelection(verifyNotes.getIntervals().indexOf(verifyNotes.getIntervals().get(0)));
        }
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                ((TextView) view).setTextColor(Color.BLACK); //Change selected text color
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });


        //set correct note to 1 (doesn't exist in map and will make note bool false) to stop displaying correct note
        displayNote(1, "Correct");
        displayNote(1, "User");
        ImageView incorrect = findViewById(R.id.redx);
        incorrect.setVisibility(View.INVISIBLE);
        ImageView correct = findViewById(R.id.greencheck);
        correct.setVisibility(View.INVISIBLE);
        if (roundNum < 10) {
            startRound();
        } else { // if they've done 10 rounds go to the stats
            Intent intent = new Intent(this, Stats.class);
            // send the intervals that they used to the next page so that they can retry with those same intervals
            intent.putStringArrayListExtra("interval_list", verifyNotes.getIntervals());
            // send the users score
            intent.putExtra("USER_SCORE", verifyNotes.getScore());
            startActivity(intent);
        }
    }

    /**
     * DISPLAYNOTE
     * Displays the based off of what maptype is needed.
     * Calls chooseNote
     *
     * @param note
     * @param mapType
     */
    public void displayNote(int note, String mapType) {
        if (mapType.compareTo("User") == 0) {
            if (noteU != null) {
                noteU.setVisibility(View.INVISIBLE);
                sharpU.setVisibility(View.INVISIBLE);
            }
            imageMap.chooseNote(note, mapType);
            noteU = findViewById(imageMap.imageNote);
            sharpU = findViewById(imageMap.imageSharp);
            if (imageMap.noteBool)
                noteU.setVisibility(View.VISIBLE);
            if (imageMap.sharpBool)
                sharpU.setVisibility(View.VISIBLE);
        } else if (mapType.compareTo("Base") == 0) {
            if (noteB != null) {
                noteB.setVisibility(View.INVISIBLE);
                sharpB.setVisibility(View.INVISIBLE);
            }
            imageMap.chooseNote(note, mapType);
            noteB = findViewById(imageMap.imageNote);
            sharpB = findViewById(imageMap.imageSharp);
            if (imageMap.noteBool)
                noteB.setVisibility(View.VISIBLE);
            if (imageMap.sharpBool)
                sharpB.setVisibility(View.VISIBLE);
        } else if (mapType.compareTo("Correct") == 0) {
            if (noteR != null) {
                noteR.setVisibility(View.INVISIBLE);
                sharpR.setVisibility(View.INVISIBLE);
            }
            imageMap.chooseNote(note, mapType);
            noteR = findViewById(imageMap.imageNote);
            sharpR = findViewById(imageMap.imageSharp);
            if (imageMap.noteBool)
                noteR.setVisibility(View.VISIBLE);
            if (imageMap.sharpBool)
                sharpR.setVisibility(View.VISIBLE);
        }
    }

    /**
     * SOUNDOFF
     * Plays the base and test notes
     */
    public void soundOff() {
        MediaPlayer midiFileMediaPlayer1;
        MediaPlayer midiFileMediaPlayer2;
        midiFileMediaPlayer1 = MediaPlayer.create(this, VerifyNotes.Notes.get(verifyNotes.getBaseNoteKey()));
        midiFileMediaPlayer1.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                mediaPlayer.reset();
                mediaPlayer.release();
            }
        });
        midiFileMediaPlayer2 = MediaPlayer.create(this, VerifyNotes.Notes.get(verifyNotes.getTestNoteKey()));
        midiFileMediaPlayer2.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                mediaPlayer.reset();
                mediaPlayer.release();
            }
        });
        midiFileMediaPlayer1.setNextMediaPlayer(midiFileMediaPlayer2);

        midiFileMediaPlayer1.start();
    }

    /**
     * PLAY
     * Calls soundoff to play the notes
     *
     * @param view
     */
    public void play(View view) {
        soundOff();
    }

    /**********************************************************
     * GET USER NOTE
     * Checks the seekbar to see which note the user has selected
     * returns the note as an int.
     *****************************************************/
    public int getUserNote() {
        SeekBar seekBar = findViewById(R.id.noteSelect);
        int seekValue = seekBar.getProgress();
        int note = 0;

        switch (seekValue) {
            case 0:
                note = 60;
                break;
            case 1:
                note = 62;
                break;
            case 2:
                note = 64;
                break;
            case 3:
                note = 65;
                break;
            case 4:
                note = 67;
                break;
            case 5:
                note = 69;
                break;
            case 6:
                note = 71;
                break;
            case 7:
                note = 72;
                break;
            case 8:
                note = 74;
                break;
            case 9:
                note = 76;
                break;
            case 10:
                note = 77;
                break;
            case 11:
                note = 79;
                break;
            case 12:
                note = 81;
        }


        RadioButton userSharp = findViewById(R.id.userSharp);
        if (userSharp.isChecked()) {
            note++;
        }
/*      commented this out incase we want to add flats later
        RadioButton userFlat = findViewById(R.id.userFlat);
        if (userFlat.isChecked()) {
            note--;
            // we shouldn't have anything lower than 60
            if (note < 60)
                note = 60;
        }
        //Toast.makeText(this, "Note = " + note, Toast.LENGTH_LONG).show();
*/
        displayNote(note, "User");
        verifyNotes.setUserNote(note);
        return note;
    }

    /**
     * returns the round number
     */
    public int getRoundNum() {
        return roundNum;
    }

    /****************************
     * RANDOM BASE NOTE
     * Get a random base note and key
     *******************************/
    public void randomBaseNote() {
        int maxNote = highestNote - verifyNotes.convertIntervalToInt();
        Random rand = new Random();
        verifyNotes.setBaseNoteKey(rand.nextInt((maxNote - 60) + 1) + 60); //rand.nextInt((max - min) + 1) + min;
    }

    /*********************
     * INTERVAL TEST NOTE
     * Get test note base off the base note and interval
     **********************/
    public void intervalTestNote() {
        verifyNotes.setTestNoteKey(verifyNotes.getBaseNoteKey() + verifyNotes.convertIntervalToInt());
        // Toast.makeText(this, "Note = " + baseNoteKey + " Note2 = " + testNoteKey, Toast.LENGTH_LONG).show();

        Random randBool = new Random();
        digression = randBool.nextBoolean();

        if (digression)
            verifyNotes.switcheroo();
    }

    /**
     * NOTEFEEDBACK
     * if the answer is correct display green check. If not display red X.
     *
     * @param correct
     */
    public void noteFeedback(boolean correct) {
        if (correct) {
            ImageView check = findViewById(R.id.greencheck);
            check.setVisibility(View.VISIBLE);
        } else {
            ImageView incorrect = findViewById(R.id.redx);
            incorrect.setVisibility(View.VISIBLE);
        }
    }
}
