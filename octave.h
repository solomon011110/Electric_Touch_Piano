#define F3 175
#define Fs3 185
#define G3 196
#define Gs3 208


#define A3 220
#define As3 233
#define B3 247
#define C4 262
#define Cs4 277
#define D4 294
#define Ds4 311
#define E4 330
#define F4 349
#define Fs4 370
#define G4 392
#define Gs4 415


#define A4 440
#define As4 466
#define B4 494
#define C5 523
#define Cs5 554
#define D5 587
#define Ds5 622
#define E5 659
#define F5 698
#define Fs5 740
#define G5 784
#define Gs5 831


#define A5 880
#define As5 932
#define B5 988
#define C6 1047
#define Cs6 1109
#define D6 1175
#define Ds6 1245
#define E6 1319
#define F6 1397


#define OCTSIZE 7
const int OCTAVE[OCTSIZE][2][8] = {
  {//bbb
    {Ds5, D5, C5, As4, Gs4, G4, F4, Ds4},
    {Ds6, D6, C6, As5, Gs5, G5, F5, Ds5}
  },
  {//bb
    {As4, A4, G4, F4, Ds4, D4, C4, As3},
    {As5, A5, G5, F5, Ds5, D5, C5, As4}
  },
  {//b
    {F4, E4, D4, C4, As3, A3, G3, F3},
    {F5, E5, D5, C5, As4, A4, G4, F4}
  },
  {//C
    {C5, B4, A4, G4, F4, E4, D4, C4},
    {C6, B5, A5, G5, F5, E5, D5, C5}
  },
  {//#
    {G4, Fs4, E4, D4, C4, B3, A3, G3},
    {G5, Fs5, E5, D5, C5, B4, A4, G4}
  },
  {//##
    {D5, Cs5, B4, A4, G4, Fs4, E4, D4},
    {D6, Cs6, B5, A5, G5, Fs5, E5, D5}
  },
  {//#####
    {B4, As4, Gs4, Fs4, E4, Ds4, Cs4, B3},
    {B5, As5, Gs5, Fs5, E5, Ds5, Cs5, B4}
  }
};

const String NOTEMARK[OCTSIZE][8] = {
  {"Eb","D ","C ","Bb","Ab","G ","F ","Eb"},//bbb
  {"Bb","A ","G ","F ","Eb","D ","C ","Bb"},//bb
  {"F ","E ","D ","C ","Bb","A ","G ","F "},//b
  {"C ","B ","A ","G ","F ","E ","D ","C "},
  {"G ","F#","E ","D ","C ","B ","A ","G "},//#
  {"D ","C#","B ","A ","G ","F#","E ","D "},//##
  {"B ","A#","G#","F#","E ","D#","C#","B "} //#####
};

const String OCTMARK[OCTSIZE][2]{
  {"bbb","Eb"},
  {"bb","Bb"},
  {"b","F"},
  {" ","C"},
  {"#","G"},
  {"##","D"},
  {"#####","B"}
};