//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 1 part 2
//Description: This program scrolls our names. The name changes if you press the button

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define LCD_X_MAX 8

void print_to_screen(uint8_t xPos, uint8_t backupIndex, char* name) {
  clear_screen();
  lcd_cursor(xPos,0);
  print_string(name + backupIndex);
  _delay_ms(350);
}

int main(void) {
  init();
  int8_t xPos = LCD_X_MAX;
  char* name1 = "Sam";
  char* name2 = "Brenden";
  uint8_t name1Len = 3;
  uint8_t name2Len = 7;

  char* currentName = name1;
  uint8_t currentLen = name1Len;
  uint8_t backupIndex = 0;

  while (1){
    if (get_btn() == 0) {
      currentName = name1;
      currentLen = name1Len;
    } else {
      currentName = name2;
      currentLen = name2Len;
    }
    print_to_screen(xPos, backupIndex, currentName);
    xPos--;
    if (xPos < 0) backupIndex++;
    if (xPos + currentLen < 0) {
      xPos = LCD_X_MAX;
      backupIndex = 0;
    }
  }
}
