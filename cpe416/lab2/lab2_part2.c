//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 2 part 2
//Description: Braitenberg vehicles 2a and 2b

#include "./library/globals.h"
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define AMBIANT_LIGHT 225
#define STANDSTILL 127
#define DIVISOR 3
#define STEP_SPEED 5
#define DECAY 3

#define MIN_SPEED 10
#define MAX_SPEED 30

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define SENSOR_LEFT 0
#define SENSOR_RIGHT 1

typedef enum State STATE;
enum State
{
	BUTTON_2A, BUTTON_2B, DONE
};

STATE braitenberg_2A();
STATE braitenberg_2B();
void motor(uint8_t num, int16_t speed);
void print_screen_data(int num);

int8_t right_current_speed = 0; // Start from a stop
int8_t left_current_speed = 0;

STATE braitenberg_2A(){

  // int8_t right_current_speed = 0; // Start from a stop
  // int8_t left_current_speed = 0;

  while(get_btn() != 1){
    print_screen_data(0);
    if (analog(SENSOR_LEFT) > AMBIANT_LIGHT) {
      left_current_speed += STEP_SPEED;
      if (left_current_speed > MAX_SPEED) left_current_speed = MAX_SPEED;
    }
    if (analog(SENSOR_RIGHT) > AMBIANT_LIGHT) {
      right_current_speed += STEP_SPEED;
      if (right_current_speed > MAX_SPEED) right_current_speed = MAX_SPEED;
    }
    left_current_speed -= DECAY;
    if (left_current_speed < MIN_SPEED) left_current_speed = MIN_SPEED;
    right_current_speed -= DECAY;
    if (right_current_speed < MIN_SPEED) right_current_speed = MIN_SPEED;
    motor(MOTOR_LEFT, left_current_speed);
    motor(MOTOR_RIGHT, right_current_speed);
  }
  return BUTTON_2B;
}

STATE braitenberg_2B(){

  // int8_t right_current_speed = 0; // Start from a stop
  // int8_t left_current_speed = 0;

  while(get_btn() != 1){
    print_screen_data(1);
    if (analog(SENSOR_RIGHT) > AMBIANT_LIGHT) {
      left_current_speed += STEP_SPEED;
      if (left_current_speed > MAX_SPEED) left_current_speed = MAX_SPEED;
    }
    if (analog(SENSOR_LEFT) > AMBIANT_LIGHT) {
      right_current_speed += STEP_SPEED;
      if (right_current_speed > MAX_SPEED) right_current_speed = MAX_SPEED;
    }
    left_current_speed -= DECAY;
    if (left_current_speed < MIN_SPEED) left_current_speed = MIN_SPEED;
    right_current_speed -= DECAY;
    if (right_current_speed < MIN_SPEED) right_current_speed = MIN_SPEED;
    motor(MOTOR_LEFT, left_current_speed);
    motor(MOTOR_RIGHT, right_current_speed);
  }
  return BUTTON_2A;
}

void print_screen_data(int num){
    clear_screen();
    lcd_cursor(0,0);
    print_num(analog(SENSOR_LEFT)); // Right side photo-resistor value
    lcd_cursor(0,1);
    print_num(analog(SENSOR_RIGHT)); // Left side photo-resisitor value
    lcd_cursor(6,0);
    if (num == 0){
        print_string("2A");
    }
    else{
        print_string("2B");
    }
    _delay_ms(200);
}

void motor(uint8_t num, int16_t speed) {
  switch (num) {
    case MOTOR_LEFT:
      speed = abs(speed);
      break;
    case MOTOR_RIGHT:
      speed = -abs(speed);
      break;
  }
  uint8_t currentSpeed = STANDSTILL + (speed / DIVISOR);
  set_servo(num, currentSpeed);
}

int main(void) {
  init();
  init_servo();
  init_adc();

  motor(MOTOR_LEFT, 0);
  motor(MOTOR_RIGHT ,0);

  STATE state = BUTTON_2A;

  while (state != DONE)
	{
		switch (state)
		{
			case BUTTON_2A:
				state = braitenberg_2A();
			  break;

      case BUTTON_2B:
				state = braitenberg_2B();
			  break;

      case DONE:
			  break;
		}
	}
  return 0;
}
