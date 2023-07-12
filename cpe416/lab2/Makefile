SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
BOARD_LIB = $(SELF_DIR)/library
SOURCE_LIB = $(wildcard $(BOARD_LIB)/*.c)
CLOCK_RATE = 16000000L

part1: lab2_part1.c $(wildcard $(BOARD_LIB)/*.c)
	avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf lab2_part1.c $(wildcard $(BOARD_LIB)/*.c)
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

part2: lab2_part2.c $(wildcard $(BOARD_LIB)/*.c)
	avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf lab2_part2.c $(wildcard $(BOARD_LIB)/*.c)
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

part3: lab2_part3.c $(wildcard $(BOARD_LIB)/*.c)
	avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf lab2_part3.c $(wildcard $(BOARD_LIB)/*.c)
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

part4: lab2_part4.c $(wildcard $(BOARD_LIB)/*.c)
	avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf lab2_part4.c $(wildcard $(BOARD_LIB)/*.c)
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

MAC_DEVICE = `ls /dev/cu*modem*`
prog_mac: main.elf
	avrdude -pm645 -P $(MAC_DEVICE) -c arduino -F -u -U flash:w:main.hex

prog_lin: main.elf
	avrdude -pm645 -P /dev/ttyACM0 -c arduino -F -u -U flash:w:main.hex

clean:
	rm -fr *.elf *.hex *.o

