package com.example.pheonixii.sonus;

import java.util.Map;
import java.util.TreeMap;


public class ImageMap {
    private Map<Integer, Integer> imageMap = null;
    public boolean noteBool = true;
    public boolean sharpBool = false;
    public int imageNote = 0;
    public int imageSharp = 0;
    private static final Map<Integer, Integer> baseImages = new TreeMap<Integer, Integer>() {{

        put(60, R.id.C4);
        put(61, R.id.C4s);
        put(62, R.id.D4);
        put(63, R.id.D4s);
        put(64, R.id.E4);
        put(65, R.id.F4);
        put(66, R.id.F4s);
        put(67, R.id.G4);
        put(68, R.id.G4s);
        put(69, R.id.A4);
        put(70, R.id.A4s);
        put(71, R.id.B4);
        put(72, R.id.C5);
        put(73, R.id.C5s);
        put(74, R.id.D5);
        put(75, R.id.D5s);
        put(76, R.id.E5);
        put(77, R.id.F5);
        put(78, R.id.F5s);
        put(79, R.id.G5);
        put(80, R.id.G5s);
        put(81, R.id.A5);
        put(82, R.id.A5s);
    }};

    private static final Map<Integer, Integer> userImages = new TreeMap<Integer, Integer>() {{

        put(60, R.id.C4U);
        put(61, R.id.C4sU);
        put(62, R.id.D4U);
        put(63, R.id.D4sU);
        put(64, R.id.E4U);
        put(65, R.id.F4U);
        put(66, R.id.F4sU);
        put(67, R.id.G4U);
        put(68, R.id.G4sU);
        put(69, R.id.A4U);
        put(70, R.id.A4sU);
        put(71, R.id.B4U);
        put(72, R.id.C5U);
        put(73, R.id.C5sU);
        put(74, R.id.D5U);
        put(75, R.id.D5sU);
        put(76, R.id.E5U);
        put(77, R.id.F5U);
        put(78, R.id.F5sU);
        put(79, R.id.G5U);
        put(80, R.id.G5sU);
        put(81, R.id.A5U);
        put(82, R.id.A5sU);
    }};

    private static final Map<Integer, Integer> correctImages = new TreeMap<Integer, Integer>() {{

        put(60, R.id.C4R);
        put(61, R.id.C4sR);
        put(62, R.id.D4R);
        put(63, R.id.D4sR);
        put(64, R.id.E4R);
        put(65, R.id.F4R);
        put(66, R.id.F4sR);
        put(67, R.id.G4R);
        put(68, R.id.G4sR);
        put(69, R.id.A4R);
        put(70, R.id.A4sR);
        put(71, R.id.B4R);
        put(72, R.id.C5R);
        put(73, R.id.C5sR);
        put(74, R.id.D5R);
        put(75, R.id.D5sR);
        put(76, R.id.E5R);
        put(77, R.id.F5R);
        put(78, R.id.F5sR);
        put(79, R.id.G5R);
        put(80, R.id.G5sR);
        put(81, R.id.A5R);
        put(82, R.id.A5sR);
    }};

    /**
     * CHOOSENOTE
     * Chooses the note.
     * @param note
     * @param mapType
     */
    public void chooseNote(int note, String mapType) {
        if (mapType.compareTo("User") == 0) {
            imageMap = ImageMap.userImages;
        } else if (mapType.compareTo("Base") == 0) {
            imageMap = ImageMap.baseImages;
        } else if (mapType.compareTo("Correct") == 0) {
            imageMap = ImageMap.correctImages;
        }


        //imageNote = imageMap.get(60);
        noteBool = true;
        imageSharp = imageMap.get(61);
        sharpBool = false;


        switch (note) {
            case 60: {
                imageNote = imageMap.get(60);
                break;
            }
            case 61: {
                imageNote = imageMap.get(60);
                imageSharp = imageMap.get(61);
                sharpBool = true;
                break;
            }
            case 62: {
                imageNote = imageMap.get(62);
                break;
            }
            case 63: {
                imageNote = imageMap.get(62);
                imageSharp = imageMap.get(63);
                sharpBool = true;
                break;
            }
            case 64: {
                imageNote = imageMap.get(64);
                break;
            }
            case 65: {
                imageNote = imageMap.get(65);
                break;
            }
            case 66: {
                imageNote = imageMap.get(65);
                imageSharp = imageMap.get(66);
                sharpBool = true;
                break;
            }
            case 67: {
                imageNote = imageMap.get(67);
                break;
            }
            case 68: {
                imageNote = imageMap.get(67);
                imageSharp = imageMap.get(68);
                sharpBool = true;
                break;
            }
            case 69: {
                imageNote = imageMap.get(69);
                break;
            }
            case 70: {
                imageNote = imageMap.get(69);
                imageSharp = imageMap.get(70);
                sharpBool = true;
                break;
            }
            case 71: {
                imageNote = imageMap.get(71);
                break;
            }
            case 72: {
                imageNote = imageMap.get(72);
                break;
            }
            case 73: {
                imageNote = imageMap.get(72);
                imageSharp = imageMap.get(73);
                sharpBool = true;
                break;
            }
            case 74: {
                imageNote = imageMap.get(74);
                break;
            }
            case 75: {
                imageNote = imageMap.get(74);
                imageSharp = imageMap.get(75);
                sharpBool = true;
                break;
            }
            case 76: {
                imageNote = imageMap.get(76);
                break;
            }
            case 77: {
                imageNote = imageMap.get(77);
                break;
            }
            case 78: {
                imageNote = imageMap.get(77);
                imageSharp = imageMap.get(78);
                sharpBool = true;
                break;
            }
            case 79: {
                imageNote = imageMap.get(79);
                break;
            }
            case 80: {
                imageNote = imageMap.get(79);
                imageSharp = imageMap.get(80);
                sharpBool = true;
                break;
            }
            case 81: {
                imageNote = imageMap.get(81);
                break;
            }
            case 82: {
                imageNote = imageMap.get(81);
                imageSharp = imageMap.get(82);
                sharpBool = true;
                break;
            }
            default:
                noteBool = false;
                sharpBool = false;
        }
    }
}