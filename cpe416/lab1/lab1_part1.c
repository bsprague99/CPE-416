//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 1 part 1
//Description: This program fades the leds 0 and 1

#include "./library/globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define LOWVALUE  0
#define HIGHVALUE 1000

void led_brightness(uint8_t ledPos, uint16_t onCount, uint16_t offCount){
  anal
  led_on(ledPos);
  for (int16_t i = 0; i < onCount; i++){
    _delay_us(1);
  }
  led_off(ledPos);
  for (int16_t i = 0; i < offCount; i++){
    _delay_us(1);
  }
};

void fade_led(uint8_t ledPos){
  int16_t onCount, offCount;
  
  onCount = LOWVALUE;
  offCount = HIGHVALUE;
  while(offCount > 0){
    led_brightness(ledPos, onCount, offCount);
    offCount--;
    onCount++;
  }
  onCount = HIGHVALUE;
  offCount = LOWVALUE;
  while(onCount > 0){
    led_brightness(ledPos, onCount, offCount);
    onCount--;
    offCount++;
  }
}

int main(void) {
  init();
  while (1){
    fade_led(0);
    fade_led(1);
  }
}
