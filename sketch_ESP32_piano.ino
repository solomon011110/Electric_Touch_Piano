#include "AQM.h"

#include "octave.h"

AQM Cld;

#define PIN_SPEAKER 17
#define PIN_KEY_UP 18
#define PIN_KEY_DOWN 5
#define THRESHOLD 36

int key = 1;
unsigned long timePushedButton = 0;
volatile int pushingNote = 0;
volatile bool isChangedKey = false;

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

void setCLDNote(String s){
    Cld.clear();
    Cld.setCursor(0, 7);
    Cld.writeChar(s);
}

void hello(){
    tone(PIN_SPEAKER, C6);
    delay(198);// 152 1/8
    tone(PIN_SPEAKER, As5);
    delay(297);// 152 1/8.
    noTone(PIN_SPEAKER);
}

void checkOct(int n){
    if(touchRead(T3) <= THRESHOLD){tone(PIN_SPEAKER, OCTAVE[key][1][n]);}
    else{tone(PIN_SPEAKER, OCTAVE[key][0][n]);}
}

void IRAM_ATTR keyDown(){
    if(!isChangedKey){
    key = (key+(OCTSIZE-1))%(OCTSIZE);
    isChangedKey = true;
    }
    timePushedButton = millis();
}

void IRAM_ATTR keyUp(){
    if(!isChangedKey){
    key = (key+1)%OCTSIZE;
    isChangedKey = true;
    }
    timePushedButton = millis();
}

void setup() {
    pinMode(PIN_SPEAKER, OUTPUT);
    
    pinMode(PIN_KEY_UP, PULLUP);
    pinMode(PIN_KEY_DOWN, PULLUP);

    attachInterrupt(PIN_KEY_UP, keyUp, FALLING);
    attachInterrupt(PIN_KEY_DOWN, keyDown, FALLING);

    Cld.init();
    hello();
}

void loop() {
    pushingNote = 0;
    pushingNote = (touchRead(T9) <= THRESHOLD) ? 1:pushingNote;
    pushingNote = (touchRead(T8) <= THRESHOLD) ? 2:pushingNote;
    pushingNote = (touchRead(T7) <= THRESHOLD) ? 4:pushingNote;
    pushingNote = (touchRead(T6) <= THRESHOLD) ? 8:pushingNote;
    pushingNote = (touchRead(T5) <= THRESHOLD) ? 16:pushingNote;
    pushingNote = (touchRead(T4) <= THRESHOLD) ? 32:pushingNote;
    pushingNote = (touchRead(T0) <= THRESHOLD) ? 64:pushingNote;

    switch (pushingNote) {
        case 1:{
            checkOct(0);
            while(true){if(THRESHOLD<touchRead(T9)){goto After;}}
        }
        case 2:{
            checkOct(1);
            while(true){if(THRESHOLD<touchRead(T8)){goto After;}}
        }
        case 4:{
            checkOct(2);
            while(true){if(THRESHOLD<touchRead(T7)){goto After;}}
        }
        case 8:{
            checkOct(3);
            while(true){if(THRESHOLD<touchRead(T6)){goto After;}}
        }
        case 16:{
            checkOct(4);
            while(true){if(THRESHOLD<touchRead(T5)){goto After;}}
        }
        case 32:{
            checkOct(5);
            while(true){if(THRESHOLD<touchRead(T4)){goto After;}}
        }
        case 64:{
            checkOct(6);
            while(true){if(THRESHOLD<touchRead(T0)){goto After;}}
        }
        default:{
            break;
        }
    }
    After:
    noTone(PIN_SPEAKER);
    if(600 < (millis() - timePushedButton)){
        isChangedKey = false;
        timePushedButton = millis();
    }
}