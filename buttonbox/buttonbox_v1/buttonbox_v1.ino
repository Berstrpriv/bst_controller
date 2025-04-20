#include <Joystick.h>
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
  

int sum = 0;
int old_sum = 0;

void setup() {

  //start serial connection

  //Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  delay(random(500, 2500));
  Joystick.begin(false);

}

void loop() {

  //read the pushbutton value into a variable

  int btn_1 = digitalRead(2);
  int btn_2 = digitalRead(3);
  int btn_3 = digitalRead(4);
  int btn_4 = digitalRead(5);
  int btn_5 = digitalRead(6);
  int btn_6 = digitalRead(7);
  int btn_7 = digitalRead(8);
  int btn_8 = digitalRead(9);

  Joystick.setButton(0, !btn_1);
  Joystick.setButton(1, !btn_2);
  Joystick.setButton(2, !btn_3);
  Joystick.setButton(3, !btn_4);
  Joystick.setButton(4, !btn_5);
  Joystick.setButton(5, !btn_6);
  Joystick.setButton(6, !btn_7);
  Joystick.setButton(7, !btn_8);

  sum = btn_1 + btn_2 + btn_3 + btn_4 + btn_5 + btn_6 + btn_7 + btn_8;

  if(sum != old_sum){
    Joystick.sendState();
  }
  delay(100);
  old_sum = sum;
}
