const int BUZZER_PIN = 2;                                        // buzzer pin
const int BUTTON_PIN = 3;                                        // button pin
int SOUND_DURATION = 500;                                        // sound duration
int SILENCE_DURATION = 50;                                       // silence duration
int MELODY[] = { 1, 1, 5, 5, 6, 6, 5, 0, 4, 4, 3, 3, 2, 2, 1 };  // melody
bool isPlaying = false;                                          // playing interrupt flag
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);        // buzzer output
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // button input
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), interrupt, RISING);
  Serial.begin(9600);
}
void loop() {
  playing();
}
void playing() {
  if (!isPlaying) {
    if (digitalRead(BUTTON_PIN) == HIGH) {  // When the button is pressed
      for (int i = 0; i < sizeof(MELODY) / sizeof(int); i++) {
        int note = MELODY[i];  // The current note
        if (note == 0) {       // The note = 0, no sound
          noTone(BUZZER_PIN);  // Turn off the buzzer
        } else {
          tone(BUZZER_PIN, 440 * pow(2, note / 6.0));  // configure the frequency of the note
          if (!isPlaying) {                            // Control if the button is pressed while playing to restart from beginning
            noTone(BUZZER_PIN);
            break;
          }
        }
        delay(SOUND_DURATION);
        noTone(BUZZER_PIN);
        delay(SILENCE_DURATION);
      }
    }
  }
}
void interrupt() {  // When the button is pressed , change the isPlaying flag.
  Serial.print(digitalRead(BUTTON_PIN));
  if (!isPlaying)
    isPlaying = true;
  else
    isPlaying = false;
}