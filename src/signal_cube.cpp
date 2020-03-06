/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Volumes/data/workspaces/signal_cube/src/signal_cube.ino"
void setup();
void loop();
#line 1 "/Volumes/data/workspaces/signal_cube/src/signal_cube.ino"
SYSTEM_THREAD(ENABLED);
static int L_GREEN = D2;
static int L_RED = D3;
static int L_RGB1_R = D4;
static int L_RGB1_G = D5;
static int L_RGB1_B = D6;
static int FAN = D7;


void setup() {
  while(1);
  pinMode(L_GREEN, OUTPUT_OPEN_DRAIN);
  pinMode(L_RED, OUTPUT_OPEN_DRAIN);
  pinMode(L_RGB1_R, OUTPUT_OPEN_DRAIN);
  pinMode(L_RGB1_G, OUTPUT_OPEN_DRAIN);
  pinMode(L_RGB1_B, OUTPUT_OPEN_DRAIN);
  pinMode(FAN, OUTPUT_OPEN_DRAIN);
}

void loop() {
  digitalWrite(L_RED, HIGH);
  digitalWrite(L_GREEN, HIGH);
  delay(1000);
  digitalWrite(L_RED, LOW);
  digitalWrite(L_GREEN, LOW);
  delay(1000);
}