//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 1 part 3
//Description: This program is a game of pong, where the buttons are used to play

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_OUT 1
#define PIN_IN  0

#define PIN0 0
#define PIN5 5
#define PIN7 7
#define PIN9 9
#define PIN11 11
#define PIN13 13

#define DELTA_TIME 50

void player_1_win(uint16_t waitTime){
  clear_screen();
  lcd_cursor(0,0);
  print_string("P1 WIN");
  lcd_cursor(0,1);
  print_num(waitTime);
}

void player_2_win(uint16_t waitTime){
  clear_screen();
  lcd_cursor(0,0);
  print_string("P2 WIN");
  lcd_cursor(0,1);
  print_num(waitTime);
}

uint8_t check_for_player1_btn(uint16_t waitTime){
  uint8_t retVal = 0;
  digital_out(PIN13, 1);
  for (uint16_t j = 0; j < waitTime; j++){
    if (digital(0) != 1) retVal = 1;
    _delay_ms(1);
  }
  digital_out(PIN13, 0); 
  return retVal;
}

uint8_t check_for_player2_btn(uint16_t waitTime){
  uint8_t retVal = 0;
  digital_out(PIN5, 1);
  for (uint16_t j = 0; j < waitTime; j++){
    if (get_btn() == 1) retVal = 1;
    _delay_ms(1);
  }
  digital_out(PIN5, 0); 
  return retVal;
}

void pass_back(uint8_t* pinArr, uint8_t reverse, uint16_t waitTime){
  for (uint8_t i = 1; i < 4; i++){
    if (!reverse) digital_out(pinArr[i], 1);
    else digital_out(pinArr[4 - i], 1);
    for (uint16_t j = 0; j < waitTime; j++){
      _delay_ms(1);
    }
    if (!reverse) digital_out(pinArr[i], 0);
    else digital_out(pinArr[4 - i], 0);
  }
}

int main(void) {
  init();

  // Set pin I/O
  digital_dir(PIN0, PIN_IN);
  digital_dir(PIN5, PIN_OUT);
  digital_dir(PIN7, PIN_OUT);
  digital_dir(PIN9, PIN_OUT);
  digital_dir(PIN11, PIN_OUT);
  digital_dir(PIN13, PIN_OUT);

  uint8_t pinArr[5] = {PIN5, PIN7, PIN9, PIN11, PIN13};
  uint16_t waitTime = 750;

  while (1){
    pass_back(pinArr, 0, waitTime);
    if(!check_for_player1_btn(waitTime)){
      player_1_win(waitTime);
      while(1);
    }
    if (waitTime - DELTA_TIME > DELTA_TIME) waitTime -= DELTA_TIME;
    pass_back(pinArr, 1, waitTime);
    if(!check_for_player2_btn(waitTime)){
      player_2_win(waitTime);
      while(1);
    }
    if (waitTime - DELTA_TIME > DELTA_TIME) waitTime -= DELTA_TIME;
  }
}
