//Name:  Samuel Sehnert and Brenden Sprague
//Assignment number Lab 1 part 4
//Description: This program uses the accelerometer to move CPE416 on the LCD

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
  init();

  char* CPE = "416";
  uint8_t backupIndex = 0;
  int8_t pos[2] = {0, 0};

  uint8_t x;
  uint8_t y;

  while (1){
    _delay_ms(150);
    clear_screen();
    x = get_accel_x();
    y = get_accel_y();

    if (x > 15 && x < 63){
      // Move 416 UP
      if (pos[1] == 1) pos[1]--;
    }
    if (x > 192 && x < 245){
      // Move 416 DOWN
      if (pos[1] == 0) pos[1]++;
    }
    if (y > 15 && y < 63){
      // Move 416 to the left
      if (pos[0] - 1 < 0) {
        pos[0] = 0;
        if (backupIndex + 1 > 2){
          backupIndex = 2;
        } else {
          backupIndex++;
        }
      } else {
        pos[0]--;
      }
    }
    if (y > 192 && y < 245){
      // Move 416 to the right
      if (backupIndex > 0) {
        backupIndex--;
      } else if (pos[0] + 1 > 7) {
        pos[0] = 7;
      } else {
        pos[0]++;
      }
    }

    lcd_cursor(pos[0], pos[1]);
    print_string(CPE + backupIndex);
  }
}
