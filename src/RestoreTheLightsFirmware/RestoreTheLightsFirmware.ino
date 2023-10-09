#include <avr/sleep.h>
#include "config.h"
#include <EnableInterrupt.h>


short int brightness = 0;
short int fadeAmount = 5;
long entred_state_time;
long current_time_in_state;
void waitStart();

void game(float T2, float T3);

void deepSleep();

void setup(){
    //Setup pins
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<COLUMNS; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    Serial.begin(9600);
    waitStart(); //Entry point, the first state
}

void loop() {
    deepSleep(); //In case Superloop is reached (it shouldn't) goes back to deepSleep state
}

void waitStart() {
    entred_state_time = millis();
    enableInterrupt(pinB[1],startGame,CHANGE);
    Serial.println("Welcome to the Restore the light Game. Press key B1 to Start");
    while (millis()-entred_state_time < 10000) {
        analogWrite(LS,brightness);
        brightness += fadeAmount;
        if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
  }
  deepSleep();
}

 void game() {

 }

 void deepSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable();
    sleep_mode();
    sleep_disable(); 
    waitStart();
 }

 void startGame(){
  disableInterrupt(pinB[1]);
  game();
}