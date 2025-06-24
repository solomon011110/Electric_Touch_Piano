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

#define OCTSIZE 3
const int OCTAVE[OCTSIZE][2][7] = {
{//bb
    {A4, G4, F4, Ds4, D4, C4, As3},
    {A5, G5, F5, Ds5, D5, C5, As4}
},
{//C
    {B4, A4, G4, F4, E4, D4, C4},
    {B5, A5, G5, F5, E5, D5, C5}
},
{//##
    {Cs5, B4, A4, G4, Fs4, E4, D4},
    {Cs6, B5, A5, G5, Fs5, E5, D5}
}
};
const String OCTMARK[OCTSIZE]{
  "bb",
  "C",
  "##"
};