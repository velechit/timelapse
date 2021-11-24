# Timelapse Timer

Photography Timer based on Atmega8 controller,  OLED display and button controls.

## Specialities:

* USB Based boot loader (based on [baerwolf](https://github.com/baerwolf/USBaspLoader)'s code)
* Minimalsitic SSD1306 driver
* SoftSwitch power on

This project contains Circuit Schematic, PCB Layout, bootloader (Customized), Main Application

This project demonstrates using linker scripts to place code bases at specific location and re-using them across different codes
* Bootloader also implements a minimalistic SSD1306 driver. As the bootloader space in ATMEGA8 is limited to 2k (start address `0x1800`), the driver is placed at `0x1600` which can be accessed through absolute addressing
* The application program (the actual timelapse code) makes use of this SSD1306 driver through absolute addressing
## Progress so far

- [x] Bootloader
- [x] SSD1306 Driver
- [x] Integrate SSD1306 Driver with bootloader, and display a USB icon when in boot load mode
- [x] Update Makefile for bootloader to generate liner script for display driver entry points to be accessed by application program
- [x] Design the PCB
- [x] Get PCB Fabricated
- [ ] Write the main application program

<br/>

**UPDATE 1: Added power off code in bootloader**

**UPDATE 2: Initial dummy firmware implemented which is simple counter**

**UPDATE 3: got the fabricated PCB, assembled, and uploaded the bootloader & the dummy firmware... till now all working**

<br/>

 _I thought of fabricating the board myself. Due to insufficient time, I have ordered from online fab. I had two options for shipment either too expensive and fast delivery or too slow with easy on pockets. I have chosen the latter, waiting for the board to arrive_

**IMPORTANT Update : I found a issue with the power on circuitory that the internal IO driver transistor is too leakey and is permanently turning on the PMOS power gate. Hence I have added additional NMOS (`2n7002`) to ground externally**


## Toolchain needed
The bootloader and firmware are developed using barebone `avr-gcc` and `avr-libc`

Install `avr-gcc` and `avr-libc`. Under Windows you may chose to use [WinAVR](http://winavr.sourceforge.net/).

Under linux (`Ubuntu` epsecially)
> `sudo apt install gcc-avr avr-libc`

You will also need gmake (generally part of the installation). If not, install using
> `sudo apt install make`

Compile using `make`

### Fuse Settings
The board is designed with external oscillator module. Hence the below fuse settings are used for `Atmega8`

```
lfuse: 1 1 0 0 0 0 0 0 = 0xC0
       | | | | | | | |
       | | | | | | | +- CKSEL0   - External Clock
       | | | | | | +--- CKSEL1
       | | | | | +----- CKSEL2
       | | | | +------- CKSEL3
       | | | +--------- SUT0     - Startup Time 0ms
       | | +----------- SUT1
       | +------------- BODEN    - Brown-out detection disabled
       +--------------- BODLEVEL - Brown-out detection level (N/A)


hfuse: 1 1 0 0 1 0 0 0 = 0xC8
       | | | | | | | |
       | | | | | | | +- BOOTRST  - Reset boots to boot loader
       | | | | | | +--- BOOTSZ0  - Boot section size 2k
       | | | | | +----- BOOTSZ1
       | | | | +------- EESAVE   - No EEPROM save on program
       | | | +--------- CKOPT    - Full Swing Clock
       | | +----------- SPIEN    - Serial programming enabled
       | +------------- WTDON    - Watchdog Timer disabled
       +--------------- RSTDISBL - Reset not disabled
```
Program the above fuses using:

> `avrdude -p atmega8 -P usb -c usbasp -U lfuse:w:0xC0:m -U hfuse:w:0xC8:m`

## Uploading the bootloader
The bootloader and the fuse settings have to be uploaded using any other method of loading (Using Arduino as ISP or USBAsp programmer). Once programmed, the controller can be soldered to the application board and the programmed bootloader be used to upload the main firmware.

## 3D models
![Board Side](board/documentation/3d/timelapse-disp.png?raw=true)
<br/>
*3D Model of display side of the board*

![Component Side](board/documentation/3d/timelapse-comp.png?raw=true)
<br/>
*3D Model of component side of the board*

## Post Fabrication
![Board Side](board/documentation/boards/front.png?raw=true)
<br/>
*Display side of the board*

![Component Side](board/documentation/boards/back.png?raw=true)
<br/>
*Component side of the board*

Full documentation can be found [here](https://raw.githack.com/velechit/timelapse/main/board/documentation/index.html)


PCB is designed using 

[![](https://www.kicad.org/img/kicad_logo_small.png)](https://www.kicad.org)

Download KiCad project files [here](board/timelapse.zip?raw=true)

Schematic can be found [here](board/schematic.pdf?raw=true)
