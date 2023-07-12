//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 2 part 1
//Description: Creating motor control functions

#include "./library/globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define STANDSTILL 127
#define DIVISOR 3

void motor(uint8_t num, int8_t speed) {
  uint8_t currentSpeed = STANDSTILL + (speed / DIVISOR);
  set_servo(num, currentSpeed);
}

int main(void) {
  init();
  init_servo();
  while (1) {
    for (uint8_t i = 0; i < 100; i++){ //speeding up moving forward 
      clear_screen();
      motor(0, i);
      motor(1, -i);
      print_num(i);
      _delay_ms(50);
    }
    for (uint8_t i = 100; i > 0; i--){ //slowing down forward
      clear_screen();
      motor(0, i);
      motor(1, -i);
      print_num(i);
      _delay_ms(50);
    }
    for (uint8_t i = 0; i < 100; i++){ //speeding up moving backwards 
      clear_screen();
      motor(0, -i);
      motor(1, i);
      print_num(i);
      _delay_ms(50);
    }
    for (uint8_t i = 100; i > 0; i--){ //slowing down backwards
      clear_screen();
      motor(0, -i);
      motor(1, i);
      print_num(i);
      _delay_ms(50);
    }
  }
}
