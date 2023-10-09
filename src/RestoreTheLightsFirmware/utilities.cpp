#include "config.h"
#include <avr/sleep.h>
#include <stdlib.h>
#include <arduino.h>
#include "utilities.h"
#include <EnableInterrupt.h>

short int brightness = 0;
short int fadeAmount = 5;
unsigned long entred_state_time;
unsigned long T1 = 0;
unsigned long T2 = 0;
unsigned long T3 = 0;
int ledsOn =COLUMNS;
int pressedButtons = 0;
game_state activeGameState = WAIT_START;
int sequence[COLUMNS] = {1,2,4,8};



void waitStart() {
    entred_state_time = millis();
    //enableInterrupt(pinB[1],startGame,CHANGE);
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


void waitTime(){
    if(T1==0){
        T1=rand()% MAX_WAIT_TIME;
        generateSequence();
        //TODO turn on all leds
        ledsOn=COLUMNS;
    }
    if(millis()-entred_state_time>=T1){
        T1=0;
        changeGameMode(DISPLAY_SEQUENCE);
    }
}

void displaySequence(){
    if(ledsOn==0){
        changeGameMode(USER_GAMEPLAY);
    }
    else if(entred_state_time-millis()<T2/ledsOn){
        //TODO turn off first led
        ledsOn--;
    }
}

void userGameplay(){
    if(entred_state_time-millis()>T3 || (pressedButtons!=sequence[ledsOn]&&pressedButtons!=0)){
        //TODO gameOver();
    }else if(ledsOn<COLUMNS){
        //TODO turn on first led sequence
        ledsOn++;
    }else{
        //TODO win
        changeGameMode(WAIT_START);
    }
}

void changeGameMode(game_state state){
    activeGameState = state;
    entred_state_time = millis();
}

void generateSequence(){
    for (int i = COLUMNS - 1; i > 0; i--) {
        int j = random(0, i + 1);
        int temp = sequence[i];
        sequence[i] = sequence[j];
        sequence[j] = temp;
    }
}