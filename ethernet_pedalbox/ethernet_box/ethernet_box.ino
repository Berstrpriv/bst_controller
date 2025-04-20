#include "Joystick.h"

// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steerin

int throttle = 0;
int clutch = 0;
int debug = 0;

int old_throttle = 0;
int old_clutch = 0;

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    //Hall sensor
    throttle = analogRead(A0);
    clutch = analogRead(A2);

    if(throttle < 550){
      throttle = 550;
    }
    if(throttle > 785){
      throttle = 785;
    }
    
    if(clutch < 620){
      clutch = 620;
    }
    if(clutch > 840){
      clutch = 840;
    }
    
    throttle = map(throttle, 550, 785, 0, 1023);
    clutch = map(clutch, 620, 840, 0, 1023);

    Joystick.setYAxis(throttle);  
    //Joystick.setZAxis(brake);
    Joystick.setThrottle(clutch);  
    if((old_clutch != clutch) || (old_throttle != throttle)){
      Joystick.sendState();
    }
    old_clutch = clutch;
    old_throttle = throttle;
}


void setup() {
// Timer shit
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  OCR1A = 500;// = (16*10^6) / (60*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  
  Joystick.setYAxisRange(0, 1023);
  delay(random(500, 1500));
  Joystick.begin(false);
  //Serial.begin(115200);
}

void loop() {
  
}
