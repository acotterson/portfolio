/* Melody
 * (cleft) 2005 D. Cuartielles for K3
 *
 * This example uses a piezo speaker to play melodies.  It sends
 * a square wave of the appropriate frequency to the piezo, generating
 * the corresponding tone.
 *
 * The calculation of the tones is made following the mathematical
 * operation:
 *
 *       timeHigh = period / 2 = 1 / (2 * toneFrequency)
 *
 * where the different tones are described as in the table:
 *
 * note   frequency   period  timeHigh
 * c          261 Hz          3830  1915  
 * d          294 Hz          3400  1700  
 * e          329 Hz          3038  1519  
 * f          349 Hz          2864  1432  
 * g          392 Hz          2550  1275  
 * a          440 Hz          2272  1136  
 * b          493 Hz          2028  1014  
 * C          523 Hz          1912  956
 *
 * http://www.arduino.cc/en/Tutorial/Melody
 */
  
int speakerPin = 9;

int length = 88; // the number of notes
int notes[] = {56,56,0,56,0,52,56,0,59,0,47,0,52,0,47,0,44,0,49,0,51,0,50,49,
               47,56,59,61,57,59,0,56,0,52,54,51,0,0,59,58,57,55,0,56,0,48,49,52,
               0,49,52,54,0,59,58,57,55,0,56,0,64,0,64,64,0,0,59,58,57,55,0,56,
               0,48,49,52,0,49,52,54,0,55,0,54,0,52,0,0}; // a space represents a rest
int beats[] = {1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,2,2,1,1,1,1,1,1,2,
               1,1,1,2,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
               2,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,2,2,1,1,2,2,2,4};
int tempo = 100;

void playTone(float tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(int note, int duration) {
  int names[] = { 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88};
  float tones[] = {16198.16183,
15289.0237,
14430.9306,
13620.9719,
12856.4779,
12134.9209,
11453.83532,
10810.97444,
10204.20658,
9631.480301,
9090.909091,
8580.685906,
8099.080916,
7644.511852,
7215.46534,
6810.485969,
6428.238997,
6067.460452,
5726.917658,
5405.487218,
5102.103291,
4815.74015,
4545.454545,
4290.342953,
4049.540458,
3822.255926,
3607.73267,
3405.242985,
3214.119498,
3033.730226,
2863.458829,
2702.743609,
2551.051646,
2407.870075,
2272.727273,
2145.171476,
2024.770229,
1911.127963,
1803.866335,
1702.621492,
1607.059749,
1516.865113,
1431.729415,
1351.371805,
1275.525823,
1203.935038,
1136.363636,
1072.585738,
1012.385115,
955.5639815,
901.9331675,
851.3107461,
803.5298746,
758.4325565,
715.8647073,
675.6859023,
637.7629114,
601.9675188,
568.1818182,
536.2928691,
506.1925573,
477.7819908,
450.9665837,
425.6553731,
401.7649373,
379.2162783,
357.9323536,
337.8429511,
318.8814557,
300.9837594,
284.0909091,
268.1464346,
253.0962786,
238.8909954,
225.4832919,
212.8276865,
200.8824686,
189.6081391,
178.9661768,
168.9214756,
159.4407278,
150.4918797,
142.0454545,
134.0732173,
126.5481393,
119.4454977


 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 86; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == 0) {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
}
