SECTIONS {
	.display 0x1600 : { *(.display)  *( .display.ro ) }
	.display.ro     : { *(.data) }
}
INSERT AFTER .text;
