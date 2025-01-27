#include "mbed.h"
#include <chrono>
#include <cstdio>

UnbufferedSerial Teraterm(USBTX, USBRX, 9600);
PwmOut led(PA_5);
DigitalIn button(PA_0);
DigitalOut buzzer(PA_1);
Timer timer;
DigitalOut LEDG(PB_0);
DigitalOut LEDB(PB_7);
DigitalOut LEDR(PB_14);
DigitalIn Button(PC_13);

typedef enum {
  State_LED_OFF,
  State_LED_RED,
  State_LED_BLUE,
  State_LED_GREEN,
  State_LED_ALL,
  State_LED_200ms,
  State_LED_1000ms,
  State_LED_2500ms
} State_LED;
State_LED State = State_LED_OFF;
State_LED Previous_State = State_LED_OFF;

// main() runs in its own thread in the OS
int main() {
    char touche;

  while (true) {
    switch (State) {
    case State_LED_OFF:
      LEDB = 0;
      LEDG = 0;
      LEDR = 0;
      Previous_State = State;
      break;

    case State_LED_GREEN:
      LEDG = 1;
      LEDB = 0;
      LEDR = 0;
      Previous_State = State;
      break;

    case State_LED_RED:
      LEDR = 1;
      LEDG = 0;
      LEDB = 0;
      Previous_State = State;
      break;

    case State_LED_BLUE:
      LEDB = 1;
      LEDG = 0;
      LEDR = 0;
      Previous_State = State;
      break;

    case State_LED_ALL:
      LEDB = 1;
      LEDG = 1;
      LEDR = 1;
      Previous_State = State;
      break;

    case State_LED_200ms:
      for (int i = 0; i < 10; i++) {
        if (Previous_State == State_LED_GREEN) {
          LEDG = !LEDG;
        } else if (Previous_State == State_LED_RED) {
          LEDR = !LEDR;
        } else if (Previous_State == State_LED_BLUE) {
          LEDB = !LEDB;
        } else if (Previous_State == State_LED_ALL) {
          LEDG = !LEDG;
          LEDR = !LEDR;
          LEDB = !LEDB;
        }
        ThisThread::sleep_for(200ms);
      }
      break;

    case State_LED_1000ms:
      for (int i = 0; i < 5; i++) {
        if (Previous_State == State_LED_GREEN) {
          LEDG = !LEDG;
        } else if (Previous_State == State_LED_RED) {
          LEDR = !LEDR;
        } else if (Previous_State == State_LED_BLUE) {
          LEDB = !LEDB;
        } else if (Previous_State == State_LED_ALL) {
          LEDG = !LEDG;
          LEDR = !LEDR;
          LEDB = !LEDB;
        }
        ThisThread::sleep_for(1000ms);
      }
      break;

    case State_LED_2500ms:
      for (int i = 0; i < 3; i++) {
        if (Previous_State == State_LED_GREEN) {
          LEDG = !LEDG;
        } else if (Previous_State == State_LED_RED) {
          LEDR = !LEDR;
        } else if (Previous_State == State_LED_BLUE) {
          LEDB = !LEDB;
        } else if (Previous_State == State_LED_ALL) {
          LEDG = !LEDG;
          LEDR = !LEDR;
          LEDB = !LEDB;
        }
        ThisThread::sleep_for(2500ms);
      }
      break;
    }

    if (Teraterm.readable()==1) 
    {
        Teraterm.read(&touche,1);
        if (touche == '1') 
        {
            State = State_LED_200ms;
        }
        else if(touche == '2')
        {
            State = State_LED_1000ms;
        }
        else if(touche == '3')
        {
            State = State_LED_2500ms;
        }
        else if(touche == 'O')
        {
            State = State_LED_OFF;
        }
        else if(touche == 'A')
        {
            State = State_LED_ALL;
        }
        else if(touche == 'G')
        {
            State = State_LED_GREEN;
        }
        else if(touche == 'B')
        {
            State = State_LED_BLUE;
        }
        else if(touche =='R')
        {
            State = State_LED_RED;
        }
    }
    ThisThread::sleep_for(200ms);
  }
}