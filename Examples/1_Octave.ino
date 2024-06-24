uint8_t buf[8] = {0}; // Keyboard report buffer

#define PIN_Z 2     // Pin for z
#define PIN_S 3     // Pin for s
#define PIN_X 4     // Pin for x
#define PIN_D 5     // Pin for D
#define PIN_C 6     // Pin for C
#define PIN_V 7     // Pin for v
#define PIN_G 8     // Pin for g
#define PIN_B 9     // Pin for b
#define PIN_H 10     // Pin for h
#define PIN_N 11    // Pin for n
#define PIN_J 12    // Pin for j
#define PIN_M 13    // Pin for m
#define buttonPin A0 // Pin for the pushbutton

int current_state = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 3600;
int counter = 0;

bool keyZ_pressed = false;
bool keyS_pressed = false;
bool keyX_pressed = false;
bool keyD_pressed = false;
bool keyC_pressed = false;
bool keyV_pressed = false;
bool keyG_pressed = false;
bool keyB_pressed = false;
bool keyH_pressed = false;
bool keyN_pressed = false;
bool keyJ_pressed = false;
bool keyM_pressed = false;

void setup() {
  Serial.begin(9600); // Setup Serial communication

  pinMode(PIN_Z, INPUT_PULLUP);
  pinMode(PIN_S, INPUT_PULLUP);
  pinMode(PIN_X, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);
  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_V, INPUT_PULLUP);
  pinMode(PIN_G, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_H, INPUT_PULLUP);
  pinMode(PIN_N, INPUT_PULLUP);
  pinMode(PIN_J, INPUT_PULLUP);
  pinMode(PIN_M, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState != current_state) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState != current_state) {
      current_state = buttonState;
      if (current_state == HIGH) {
        counter++;
        if (counter == 1) {
          // handleButtonPress(); // No need to handle button press here
        }
      } else {
        counter = 0;
      }
    }
  }

  // Update key press states
  keyZ_pressed = digitalRead(PIN_Z) == HIGH;
  keyS_pressed = digitalRead(PIN_S) == HIGH;
  keyX_pressed = digitalRead(PIN_X) == HIGH;
  keyD_pressed = digitalRead(PIN_D) == HIGH;
  keyC_pressed = digitalRead(PIN_C) == HIGH;
  keyV_pressed = digitalRead(PIN_V) == HIGH;
  keyG_pressed = digitalRead(PIN_G) == HIGH;
  keyB_pressed = digitalRead(PIN_B) == HIGH;
  keyH_pressed = digitalRead(PIN_H) == HIGH;
  keyN_pressed = digitalRead(PIN_N) == HIGH;
  keyJ_pressed = digitalRead(PIN_J) == HIGH;
  keyM_pressed = digitalRead(PIN_M) == HIGH;

  buf[0] = 0; 
  buf[2] = 0; // Keycode for now
  buf[3] = 0; // Additional keycode
  buf[4] = 0; // Additional keycode
  buf[5] = 0; // Additional keycode

  int bufIndex = 2; // Start filling from buf[2]

  // Add the keycodes for the keys that are pressed
  // You will need to replace the keycodes with the correct ones for your keys
  if (keyZ_pressed) buf[bufIndex++] = 29; // Z keycode
  if (keyS_pressed) buf[bufIndex++] = 22; // S keycode
  if (keyX_pressed) buf[bufIndex++] = 27; // X keycode
  if (keyD_pressed) buf[bufIndex++] = 7;  // D keycode
  if (keyC_pressed) buf[bufIndex++] = 6;  // C keycode
  if (keyV_pressed) buf[bufIndex++] = 25; // V keycode
  if (keyG_pressed) buf[bufIndex++] = 10; // G keycode
  if (keyB_pressed) buf[bufIndex++] = 5;  // B keycode
  if (keyH_pressed) buf[bufIndex++] = 11; // H keycode
  if (keyN_pressed) buf[bufIndex++] = 17; // N keycode
  if (keyJ_pressed) buf[bufIndex++] = 13; // J keycode
  if (keyM_pressed) buf[bufIndex++] = 16; // M keycode

  Serial.write(buf, 8);

  releaseKey();
}

void releaseKey() {
  for (int i = 2; i < 6; i++) {
    buf[i] = 0;
  }
}