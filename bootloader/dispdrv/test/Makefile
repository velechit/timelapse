CC=avr-gcc
OBJCOPY=avr-objcopy
MCU=atmega8
ARCH_FLAGS=-mmcu=$(MCU)
PROGRAMMER=usbasp
CFLAGS=-I.. -DF_CPU=12000000UL -Os
LDFLAGS=-Wl,-Tlinkdrv.ld,--defsym=__TEXT_REGION_LENGTH__=5k
AVRDUDE=avrdude

all: main.hex

main.hex: main.elf
	$(OBJCOPY) -O ihex -j .data -j .text -j .bss $< $@

main.elf: main.o
	$(CC) $(ARCH_FLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(ARCH_FLAGS) -o $@ -c $< $(CFLAGS)

.PHONEY: clean program

program: main.hex
	$(AVRDUDE) -D -p $(MCU) -P usb -c $(PROGRAMMER) -U flash:w:main.hex:i 

clean:
	rm -rf *.o *.elf *.hex
