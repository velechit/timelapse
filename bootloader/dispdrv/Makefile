CC=avr-gcc
OBJCOPY=avr-objcopy
MCU=atmega8
ARCH_FLAGS=-mmcu=$(MCU)
PROGRAMMER=usbasp
CFLAGS=-I. -DDRIVER_COMPILE -DF_CPU=12000000UL -Os
LDFLAGS=-Wl,-Tdrvmap.ld
AVRDUDE=avrdude
OBJDUMP=avr-objdump

all: main.hex symtab

main.hex:  main.elf
	$(OBJCOPY) -O ihex -j .display $< $@

main.elf: main.o SSD1306.o
	$(CC) $(ARCH_FLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(ARCH_FLAGS) -o $@ -c $< $(CFLAGS)

.PHONY: clean program

program: main.hex
	$(AVRDUDE) -p $(MCU) -P usb -c $(PROGRAMMER) -U flash:w:main.hex:i 

symtab: main.elf
	$(OBJDUMP) --sym main.elf | grep F | grep -E "USBLogo|SSD1306" | \
		awk 'BEGIN { print "SECTIONS {\n"} END {print "}\nINSERT AFTER .text;"} { a=strtonum("0x" $$1); printf "      %s = 0x%04X ;\n",$$NF,a }' \
		> linkdrv.ld

clean:
	rm -rf *.o *.elf *.hex linkdrv.ld
