const int NOTE[36] = {
  175, //F3 0
  185,
  196,
  208,
  220,
  233,
  247,

  262, //C4 7
  277,
  294,
  311,
  330,

  349, //F4 12
  370,
  392,
  415,
  440,
  466,
  494,

  523, //C5 19
  554,
  587,
  622,
  659,

  698, //F5 24
  740,
  784,
  831,
  880,
  932,
  988,

  1047, //C6 31
  1109,
  1175,
  1245,
  1319
};

const int SCALE[2][8] = {
  {2,2,1,2,2,2,1,0},
  {2,1,2,2,1,2,2,0}
};
const String NOTEMARK[2][12] = {
  {"F ","F#","G ","G#","A ","A#","B ","C ","C#","D ","D#","E "},
  {"F ","Gb","G ","Ab","A ","Bb","B ","C ","Db","D ","Eb","E "}
};

#define KEYSIZE 12

const String KEYMARK[KEYSIZE][3] = {
  {"b","F","Dm"},
  {"bbbbbb","Gb","Ebm"},
  {"#","G","Em"},
  {"bbbb","Ab","Fm"},
  {"###","A","F#m"},
  {"bb","Bb","Gm"},
  {"#####","B","G#m"},
  {" ","C","Am"},
  {"bbbbb","Db","Bbm"},
  {"##","D","Bm"},
  {"bbb","Eb","Cm"},
  {"####","E","C#m"}
};

// const String KEYMARK[KEYSIZE][3] = {
//   {"bbbbbb","Gb","Ebm"},
//   {"bbbbb","Db","Bbm"},
//   {"bbbb","Ab","Fm"},
//   {"bbb","Eb","Cm"},
//   {"bb","Bb","Gm"},
//   {"b","F","Dm"},
//   {" ","C","Am"},
//   {"#","G","Em"},
//   {"##","D","Bm"},
//   {"###","A","F#m"},
//   {"####","E","C#m"},
//   {"#####","B","G#m"}
// };

// const int KEYINDEX[KEYSIZE] = {
//   1,  //Gb bbbbbb | F# ######
//   8, //Db bbbbb
//   3, //Ab bbbb
//   10,//Eb bbb
//   5, //Bb bb
//   0, //F  b
//   7, //C
//   2, //G  #
//   9, //D  ##
//   4, //A  ###
//   11,//E  ####
//   6  //B  #####
// };