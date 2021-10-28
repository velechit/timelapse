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


## 3D models
![Component Side](board/documentation/3d/timelapse-disp.png?raw=true)
*3D Model of display side of the board*

![Component Side](board/documentation/3d/timelapse-comp.png?raw=true)
*3D Model of component side of the board*

Full documentation can be found [here](board/documentation/index.html)


PCB is designed using 

[![](https://www.kicad.org/img/kicad_logo_small.png)](https://www.kicad.org)

Download KiCad project files [here](board/timelapse.zip?raw=true)

Schematic can be found [here](board/schematic.pdf?raw=true)
