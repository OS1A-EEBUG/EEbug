clean:
	rm *.elf *.o *.hex *.lst

build: main.c hardware.c bug.h
	avr-gcc -mmcu=attiny45 -I. -std=gnu11 -Wall -Werror -Wextra -Os -c main.c hardware.c
	avr-gcc -mmcu=attiny45 -I. -std=gnu11 main.o hardware.o -o main.elf
	avr-objdump -h -S main.elf > main.lst
	avr-objcopy -R .eeprom -O ihex main.elf main.hex

flash: main.hex
	avrdude -c avrispmkII -p attiny45 -U flash:w:main.hex
