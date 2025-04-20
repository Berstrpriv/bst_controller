#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  2, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steerin

int handbrake = 0;
void setup() {
  // Initialize Button Pins
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
 Serial.begin(115200);
  // Initialize Joystick Library
  delay(random(500, 1500));
  Joystick.begin(false);
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 8;

// Last state of the button
int lastButtonState[2] = {0,0};

void loop() {

  // Read pin values
  for (int index = 0; index < 2; index++)
  {
    int currentButtonState = !digitalRead(index+8);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  Joystick.sendState();
  delay(100);
}
