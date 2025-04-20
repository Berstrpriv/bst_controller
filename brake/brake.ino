#include "HX711.h"
#include "Joystick.h"

// Create Joystick - minimal config (Z axis only)
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, true,   // Z Axis only
  false, false, false, 
  false, false, false);  

// HX711 setup
const int LOADCELL_DOUT_PIN = A2;
const int LOADCELL_SCK_PIN = A3;
HX711 scale;

// Timer variables
volatile long lastReading = -1;

ISR(TIMER1_COMPA_vect) {
  long raw = scale.read() - 390000;
  raw = constrain(raw, 0, 1500000);

  int mappedReading = map(raw, 0, 1500000, 0, 1023);

  // Bug workaround — avoid ghost brake input
  if (mappedReading >= 1000 && lastReading <= 5) {
    mappedReading = 0;
  }

  if (mappedReading != lastReading) {
    Joystick.setZAxis(mappedReading);
    Joystick.sendState(); // only send when value changes
    lastReading = mappedReading;
  }
}

void setup() {
  // Timer1 setup ~1kHz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 500; // ~500–1000Hz
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  delay(random(500, 1500));
  Joystick.begin(false);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
}

void loop() {
  // Nothing to do here
}
