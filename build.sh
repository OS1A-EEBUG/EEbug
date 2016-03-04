#!/bin/sh
source="${1}.c"
object="${1}.o"
elfobj="${1}.elf"
hexobj="${1}.hex"
lstout="${1}.lst"
echo "Compiling..."
avr-gcc -I. -c -std=gnu11 -Os -Wall -Wextra -Werror -mmcu=attiny45 -Os $source -o $object
echo "Linking..."
avr-gcc -I. -mmcu=attiny45 $object -o $elfobj
echo "Generating disassembly for verification..."
avr-objdump -h -S $elfobj > $lstout 
echo "Generating hex..."
avr-objcopy -O ihex -R .eeprom $elfobj $hexobj
