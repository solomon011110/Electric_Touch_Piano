#include "AQM.h"

#include "octave.h"

AQM LCD;

#define PIN_SPEAKER 17
#define PIN_KEY_UP 18
#define PIN_KEY_DOWN 5
#define PIN_OCT_CHANGE 19
#define THRESHOLD 36

int key = 3;
int oct = 0;
unsigned long timePushedButton = 0;
volatile bool isPushedButton = false;

/*
ESP32
^
    0 1 2 3

9 8 7 6 5 4

T0: 4
T1: 0(x)
T2: 2
T3: 15

T4: 13
T5: 12
T6: 14
T7: 27
T8: 33
T9: 32

<<I2C>>
SCL: 22
CDA: 21

*/

void setLCDKey(){
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.writeString(OCTMARK[key][0]);
    LCD.setCursor(6, 1);
    LCD.writeString(OCTMARK[key][1]);
}

void setLCDNote(int note){
    LCD.setCursor(0, 1);
    LCD.writeString(NOTEMARK[key][note]);
}

void hello(){
    setLCDKey();
    tone(PIN_SPEAKER, C6);
    delay(198);// 152 1/8
    tone(PIN_SPEAKER, As5);
    delay(297);// 152 1/8.
    noTone(PIN_SPEAKER);
}

void checkOct(int n){
    if(touchRead(T3) <= THRESHOLD){tone(PIN_SPEAKER, OCTAVE[key][(oct+1)%2][n]);}
    else{tone(PIN_SPEAKER, OCTAVE[key][oct][n]);}

    setLCDNote(n);
}

void IRAM_ATTR keyDown(){
    if(!isPushedButton){
        key = (key+(OCTSIZE-1))%(OCTSIZE);
        isPushedButton = true;
    }
    timePushedButton = millis();
}

void IRAM_ATTR keyUp(){
    if(!isPushedButton){
        key = (key+1)%OCTSIZE;
        isPushedButton = true;
    }
    timePushedButton = millis();
}

void IRAM_ATTR OctChange(){
    if(!isPushedButton){
        oct = (oct+1)%2;
        isPushedButton = true;
    }
    timePushedButton = millis();
}

void setup() {
    pinMode(PIN_SPEAKER, OUTPUT);
    
    pinMode(PIN_KEY_UP, PULLUP);
    pinMode(PIN_KEY_DOWN, PULLUP);
    pinMode(PIN_OCT_CHANGE, PULLUP);

    attachInterrupt(PIN_KEY_UP, keyUp, FALLING);
    attachInterrupt(PIN_KEY_DOWN, keyDown, FALLING);
    attachInterrupt(PIN_OCT_CHANGE, OctChange, FALLING);

    LCD.begin();
    hello();
}

void loop() {
    if(touchRead(T2) <= THRESHOLD){
        checkOct(7);
        while(true){if(THRESHOLD<touchRead(T2)){break;}}
    }
    else if(touchRead(T4) <= THRESHOLD){
        checkOct(6);
        while(true){if(THRESHOLD<touchRead(T4)){break;}}
    }
    else if(touchRead(T5) <= THRESHOLD){
        checkOct(5);
        while(true){if(THRESHOLD<touchRead(T5)){break;}}
    }
    else if(touchRead(T6) <= THRESHOLD){
        checkOct(4);
        while(true){if(THRESHOLD<touchRead(T6)){break;}}
    }
    else if(touchRead(T7) <= THRESHOLD){
        checkOct(3);
        while(true){if(THRESHOLD<touchRead(T7)){break;}}
    }
    else if(touchRead(T8) <= THRESHOLD){
        checkOct(2);
        while(true){if(THRESHOLD<touchRead(T8)){break;}}
    }
    else if(touchRead(T9) <= THRESHOLD){
        checkOct(1);
        while(true){if(THRESHOLD<touchRead(T9)){break;}}
    }
    else if(touchRead(T0) <= THRESHOLD){
        checkOct(0);
        while(true){if(THRESHOLD<touchRead(T0)){break;}}
    }

    noTone(PIN_SPEAKER);
    if( isPushedButton && (255 < (millis() - timePushedButton)) ){
        setLCDKey();
        isPushedButton = false;
        timePushedButton = millis();
    }
}