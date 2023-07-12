// Name:  Samuel Sehnert and Brenden Sprague
// Assignment number Lab 2 part 4
// Description: Line Following Robot

#include <stdlib.h>
#include "./library/globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define STANDSTILL 127
#define DIVISOR 3

#define K_p 0.25

#define SENSOR_0 2
#define SENSOR_1 3
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

#define BASE_SPEED 15

void motor(uint8_t num, int16_t speed);

int16_t calculateLineError();

void testPrint(int16_t a, int16_t b){
  clear_screen();
  lcd_cursor(0,0);
  print_string("L: ");
  print_num(a);
  lcd_cursor(0,1);
  print_string("R: ");
  print_num(b);
  _delay_ms(100);
};

int main () {
  init();
  motor(MOTOR_LEFT, 0);
  motor(MOTOR_RIGHT, 0);

  int16_t lineError;

  while (1){
    lineError = K_p * calculateLineError();
    motor(MOTOR_LEFT, BASE_SPEED - lineError);
    motor(MOTOR_RIGHT, BASE_SPEED + lineError);
    testPrint(
      BASE_SPEED - lineError, BASE_SPEED + lineError
    );
    _delay_ms(50);
  }
  return 0;
}

void motor(uint8_t num, int16_t speed) {
  switch (num) {
    case MOTOR_LEFT:
      if (speed < 0) speed = 0;
      if (speed > 100) speed = 100;
      speed = abs(speed) * 1.2;
      break;
    case MOTOR_RIGHT:
      if (speed < 0) speed = 0;
      if (speed > 100) speed = 100;
      speed = -abs(speed) * 0.8;
      break;
  }
  uint8_t currentSpeed = STANDSTILL + (speed / DIVISOR);
  set_servo(num, currentSpeed);
}

int16_t calculateLineError(){
  return analog(SENSOR_0) - analog(SENSOR_1);
}

