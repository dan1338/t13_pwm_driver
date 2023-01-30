main.hex: main.bin
	avr-objcopy -j .text -j .data -O ihex $< $@

main.bin: main.c
	avr-gcc -Wall -Os -g -mmcu=attiny13a $< -o $@

check:
	avrdude -c usbasp -p t13a

flash:
	avrdude -c usbasp -p t13a -U flash:w:main.hex:i

clean:
	rm main.bin main.hex

.PHONY: check flash clean
