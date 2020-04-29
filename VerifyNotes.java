package com.example.pheonixii.sonus;

import android.graphics.Color;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Map;
import java.util.Random;
import java.util.TreeMap;

public class VerifyNotes {

    private ArrayList<String> intervals;

    // User note to be used by the verifyNote function.
    private int userNote;

    // The keys are for the note map
    private int baseNoteKey = 0;
    // The test note is the note the user needs to guess; the second note that gets played
    private int testNoteKey = 0;

    private String interval;

    Spinner spinner;

    double score = 0.0;

    /**
     * GETTERS and SETTERS
     */

    public ArrayList<String> getIntervals() {
        return intervals;
    }

    public void setIntervals(ArrayList<String> intervals) {
        this.intervals = intervals;
    }

    public int getUserNote() {
        return userNote;
    }

    public void setUserNote(int userNote) {
        this.userNote = userNote;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }

    public Spinner getSpinner() {
        return spinner;
    }

    public void setSpinner(Spinner spinner) {
        this.spinner = spinner;
    }

    public String getInterval() {
        return interval;
    }

    public void setInterval(String interval) {
        this.interval = interval;
    }

    public int getBaseNoteKey() {
        return baseNoteKey;
    }

    public void setBaseNoteKey(int baseNoteKey) {
        this.baseNoteKey = baseNoteKey;
    }

    public int getTestNoteKey() {
        return testNoteKey;
    }

    public void setTestNoteKey(int testNoteKey) {
        this.testNoteKey = testNoteKey;
    }

    public static final Map<Integer, Integer> Notes = new TreeMap<Integer, Integer>() {{
        put(48, R.raw.fourty_eight);
        put(49, R.raw.fourty_nine);
        put(50, R.raw.fifty);
        put(51, R.raw.fifty_one);
        put(52, R.raw.fifty_two);
        put(53, R.raw.fifty_three);
        put(54, R.raw.fifty_four);
        put(55, R.raw.fifty_five);
        put(56, R.raw.fifty_six);
        put(57, R.raw.fifty_seven);
        put(58, R.raw.fifty_eight);
        put(59, R.raw.fifty_nine);
        put(60, R.raw.sixty);
        put(61, R.raw.sixty_one);
        put(62, R.raw.sixty_two);
        put(63, R.raw.sixty_three);
        put(64, R.raw.sixty_four);
        put(65, R.raw.sixty_five);
        put(66, R.raw.sixty_six);
        put(67, R.raw.sixty_seven);
        put(68, R.raw.sixty_eight);
        put(69, R.raw.sixty_nine);
        put(70, R.raw.seventy);
        put(71, R.raw.seventy_one);
        put(72, R.raw.seventy_two);
        put(73, R.raw.seventy_three);
        put(74, R.raw.seventy_four);
        put(75, R.raw.seventy_five);
        put(76, R.raw.seventy_six);
        put(77, R.raw.seventy_seven);
        put(78, R.raw.seventy_eight);
        put(79, R.raw.seventy_nine);
        put(80, R.raw.eighty);
        put(81, R.raw.eighty_one);
        put(82, R.raw.eighty_two);
        put(83, R.raw.eighty_three);
        put(84, R.raw.eighty_four);
        put(85, R.raw.eighty_five);
        put(86, R.raw.eighty_six);
        put(87, R.raw.eighty_seven);
        put(88, R.raw.eighty_eight);
        put(89, R.raw.eighty_nine);
        put(90, R.raw.ninety);
        put(91, R.raw.ninety_one);
        put(92, R.raw.ninety_two);
        put(93, R.raw.ninety_three);
        put(94, R.raw.ninety_four);
        put(95, R.raw.ninety_five);
        put(96, R.raw.ninety_six);
        put(97, R.raw.ninety_seven);
        put(98, R.raw.ninety_eight);
        put(99, R.raw.ninety_nine);
        put(100, R.raw.one_hundred);
        put(101, R.raw.one_hundred_one);
        put(102, R.raw.one_hundred_two);
        put(103, R.raw.one_hundred_three);
    }};

    /*********************
     * CONVERT INTERVAL TO INT
     * Intervals are strings and need to be ints
     **********************/
    public int convertIntervalToInt() {
        switch (interval) {
            case "Perfect Unison":
                return 0;
            case "Minor Second":
                return 1;
            case "Major second":
                return 2;
            case "Minor Third":
                return 3;
            case "Major Third":
                return 4;
            case "Perfect Fourth":
                return 5;
            case "Perfect Fifth":
                return 7;
            case "Minor Sixth":
                return 8;
            case "Major Sixth":
                return 9;
            case "Minor Seventh":
                return 10;
            case "Major Seventh":
                return 11;
            case "Perfect Octave":
                return 12;
            default:
                //Toast.makeText(this, "FAIl", Toast.LENGTH_SHORT).show();
                break;
        }
        return -1; //fail
    }

    /**
     * RANDOM INTERVAL
     * Chooses a random interval which will be used to determine the test note.
     * Uses only intervals that user has chosen.
     */
    public String randomInterval() {
        String answerInterval = "Empty";
        if (!intervals.isEmpty())
            answerInterval = intervals.get(new Random().nextInt(intervals.size()));
        return answerInterval;
    }


    /**
     * VERIFY INTERVAL
     * Check if they chose the correct interval. If so return true else return false.
     */
    public boolean verifyInterval() {
        String correctInterval = interval;
        String userInterval = spinner.getSelectedItem().toString();

        boolean isCorrect = correctInterval.equals(userInterval);
        // if its wrong display the correct one in green
        if (!isCorrect) {
            spinner.setSelection(intervals.indexOf(interval));
            spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                    ((TextView) view).setTextColor(Color.GREEN); //Change selected text color
                }

                @Override
                public void onNothingSelected(AdapterView<?> parent) {

                }
            });
            spinner.setEnabled(false);
        }
        return isCorrect;
    }


    /**
     * VERIFY NOTE
     *
     * @return
     */
    public boolean verifyNote() {
        return getTestNoteKey() == userNote;
    }

    /**
     * VERIFY ANSWER
     * Check if they got the interval correct. If so add .5 to their score.
     * Check if they got the note correct. If so add another .5 to their score.
    */
    public void verifyAnswer() {
        if (verifyInterval()) {
            score += .5;
        }

        if (verifyNote()) {
            score += .5;
        }
    }

    public void switcheroo(){
        int tempBase = baseNoteKey;
        baseNoteKey = testNoteKey;
        testNoteKey = tempBase;
    }
}




