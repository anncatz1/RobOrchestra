#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
#include <Servo.h>

MIDI_CREATE_DEFAULT_INSTANCE();

Servo strummer;
int strum_delay = 50;
int sol_delay = 500;
int which = 0; //Next direction to sweep the arm

int SOL_1 = 22;
int SOL_2 = 23;
int SOL_3 = 24;
int SOL_4 = 25;
int SOL_5 = 26;
int SOL_6 = 27;
int SOL_7 = 28;
int SOL_8 = 29;
int SOL_9 = 30;
int SOL_10 = 31;
int SOL_11 = 32;
int SOL_12 = 33;
int SOL_13 = 34;
int SOL_14 = 35;
int SOL_15 = 36;
int SOL_16 = 37;

int solenoidarray[] = {SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, SOL_8, SOL_9, SOL_10, SOL_11, SOL_12, SOL_13, SOL_14, SOL_15, SOL_16};
int nsolenoids = 16;

const int chordlen = 4;
const int numchords = 7;

int C[chordlen] = {SOL_15,0,0,0};
int D[chordlen] = {SOL_2, SOL_6,SOL_10, 0};
int E[chordlen] = {SOL_4, SOL_8,SOL_12,SOL_14};
int F[chordlen] = {SOL_4, SOL_8,SOL_12,SOL_14};
int G[chordlen] = {SOL_6, SOL_11, SOL_14, 0};
int A[chordlen] = {SOL_2, SOL_5, 0, 0};
int B[chordlen] = {SOL_4, SOL_7,SOL_10,SOL_14};


int Cm[chordlen] = {SOL_7,SOL_11,SOL_15};
int Dm[chordlen] = {SOL_2, SOL_6, SOL_9 };
int Em[chordlen] = {SOL_8,SOL_11,SOL_14 };
int Fm[chordlen] = {SOL_1, SOL_9,SOL_15};
int Gm[chordlen] = {SOL_6,SOL_11,SOL_13 };
int Am[chordlen] = {SOL_2,0,0,0};
int Bm[chordlen] = {SOL_4, SOL_6,SOL_10,SOL_14};

int C7[chordlen] = {SOL_13,0,0,0};
int D7[chordlen] = {SOL_2,SOL_10,0,0};
int E7[chordlen] = {SOL_10,SOL_14,0,0 };
int F7[chordlen] = {SOL_2,SOL_7,SOL_9,0};
int G7[chordlen] = {SOL_6,SOL_9,SOL_14,0};
int CHORD_A7[chordlen] = {SOL_5,0,0,0}; //Because apparently A7 was taken already
int B7[chordlen] = {SOL_2,SOL_7,SOL_10,SOL_14};


int *major[numchords] = {C,D,E,F,G,A,B};
int *minor[numchords] = {Cm,Dm,Em,Fm,Gm,Am,Bm};
int *other[numchords] = {C7,D7,E7,F7,CHORD_A7,B7};

/*  note number */
int C_midi = 60;
int D_midi = 62;
int E_midi = 64;
int F_midi = 65;
int G_midi = 67;
int A_midi = 79;
int B_midi = 71; 

void play(int note[]){
  
  for(int i=0;i<chordlen;i++){
    digitalWrite(note[i],HIGH);
  }
  
  delay(sol_delay);

  if(which == 1){
    hit();
    which = -1;
  } else{
    hit2();
     which = 1;
  }
  
  
  
  for(int i=0;i<chordlen;i++){
    digitalWrite(note[i],LOW);
  }
}


void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  int note;
  pitch = pitch % 12 + 60;
  
  if(channel == 3) {
    int Note; 
    
    if(pitch == C_midi){
        Note = 0;
    } else if(pitch == D_midi){
      Note = 1;
    } else if(pitch == E_midi){
        Note = 2;
    } else if(pitch == F_midi){
        Note = 3;
    } else if(pitch == G_midi){
        Note = 4;
    } else if(pitch == A_midi){
        Note = 5;
    } else if(pitch == B_midi){
        Note = 6;
    }

    int chord[4] = {0,0,0,0};
    
    if(velocity == 50) {
      for(int x = 0; x < 4; x++){
        chord[x] = major[Note][x];
      }   
    } else if(velocity == 100) {
      for(int x = 0; x < 4; x++){
        chord[x] = minor[Note][x];
      }
    } else {
      for(int x = 0; x < 4; x++){
        chord[x] = other[Note][x];
      }
    }

    play(chord);
  }
}


void setup()
{
  strummer.attach(53);
  for(int x = 0; x < nsolenoids; x++){
    pinMode(solenoidarray[x], OUTPUT);
    digitalWrite(solenoidarray[x], LOW);
  }
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOn();
}

void loop()
{ 
  //MIDI.read();
  play(D);
  delay(1000);
}


void hit() {
  strummer.write(100);
  delay(strum_delay);
}

void hit2() {
  strummer.write(10);
  delay(strum_delay);
}

