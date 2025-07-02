#include "octave.h"
#include "AQM.h"
AQM LCD;

#define PIN_SPEAKER 17
#define PIN_KEY_UP 18
#define PIN_KEY_DOWN 5
#define PIN_SCALE_CHANGE 19
#define THRESHOLD 36

int key = 7;
int oct = 0;
int scale = 0;
String notemark[8];
int OCTAVE[2][8];
volatile unsigned long timePushedButton = 0;
volatile bool isPushedButton = false;

/*
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

<<LCD>>
SCL: 22
CDA: 21

*/

void setKey(int keyIndex, int isMinorScale){
    int index = (keyIndex+(9*isMinorScale))%KEYSIZE;

    for(int i = 0; i<2; i++){
        for(int j = 0; j<8; j++){
            OCTAVE[i][j] = NOTE[index];
            index = index + SCALE[isMinorScale][j];
    }
  }
    setNotemark(keyIndex, scale);
}

void setNotemark(int keyIndex, int isMinorScale){
    int index = (keyIndex+(9*isMinorScale))%KEYSIZE;
    int sb = (keyIndex == 1 || keyIndex%2 == 0) ? 1 : 0;

    for(int i = 0; i<8; i++){
        notemark[i] = NOTEMARK[sb][index];
        index = (index+SCALE[isMinorScale][i])%KEYSIZE;
    }
}

void setLCDKey(){
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.writeString(KEYMARK[key][0]);
    LCD.setCursor(5, 1);
    LCD.writeString(KEYMARK[key][1+scale]);
}

void setLCDNote(int note){
    LCD.setCursor(0, 1);
    LCD.writeString(notemark[note]);
}

void hello(){
    tone(PIN_SPEAKER, NOTE[31]); delay(198);// 152 1/8
    tone(PIN_SPEAKER, NOTE[29]); delay(297);// 152 1/8.
    noTone(PIN_SPEAKER);
}

void playNote(int n){
    if(touchRead(T3) <= THRESHOLD){tone(PIN_SPEAKER, OCTAVE[(oct+1)%2][n]);}
    else{tone(PIN_SPEAKER, OCTAVE[oct][n]);}
    setLCDNote(n);
}

void IRAM_ATTR keyDown(){
    if(!isPushedButton){
        isPushedButton = true;
        timePushedButton = millis();
        key = (key+(KEYSIZE-1))%(KEYSIZE);
        setKey(key,scale);
    }
}

void IRAM_ATTR keyUp(){
    if(!isPushedButton){
        isPushedButton = true;
        timePushedButton = millis();
        key = (key+1)%KEYSIZE;
        setKey(key,scale);
    }
}

void IRAM_ATTR scaleChange(){
    if(!isPushedButton){
        isPushedButton = true;
        timePushedButton = millis();
        scale = (scale+1)%2;
        setKey(key,scale);
    }   
}

void setup() {
    pinMode(PIN_SPEAKER, OUTPUT);
    
    pinMode(PIN_KEY_UP, PULLUP);
    pinMode(PIN_KEY_DOWN, PULLUP);
    pinMode(PIN_SCALE_CHANGE, PULLUP);

    attachInterrupt(PIN_KEY_UP, keyUp, FALLING);
    attachInterrupt(PIN_KEY_DOWN, keyDown, FALLING);
    attachInterrupt(PIN_SCALE_CHANGE, scaleChange, FALLING);

    LCD.begin();

    setKey(key,scale);
    setLCDKey();
    
    hello();
}

void loop() {
    if(touchRead(T2) <= THRESHOLD){
        playNote(0);
        while(touchRead(T2) <= THRESHOLD){}
    }
    else if(touchRead(T4) <= THRESHOLD){
        playNote(1);
        while(touchRead(T4) <= THRESHOLD){}
    }
    else if(touchRead(T5) <= THRESHOLD){
        playNote(2);
        while(touchRead(T5) <= THRESHOLD){}
    }
    else if(touchRead(T6) <= THRESHOLD){
        playNote(3);
        while(touchRead(T6) <= THRESHOLD){}
    }
    else if(touchRead(T7) <= THRESHOLD){
        playNote(4);
        while(touchRead(T7) <= THRESHOLD){}
    }
    else if(touchRead(T8) <= THRESHOLD){
        playNote(5);
        while(touchRead(T8) <= THRESHOLD){}
    }
    else if(touchRead(T9) <= THRESHOLD){
        playNote(6);
        while(touchRead(T9) <= THRESHOLD){}
    }
    else if(touchRead(T0) <= THRESHOLD){
        playNote(7);
        while(touchRead(T0) <= THRESHOLD){}
    }

    noTone(PIN_SPEAKER);
    if( isPushedButton && (255 < (millis() - timePushedButton)) ){
        setLCDKey();
        isPushedButton = false;
        timePushedButton = millis();
    }
}