#include "display.h"
#include "spi.h"
#include "font.h"
#include <avr/io.h>

static spi_channel_t spi_channel;

void cmd(uint8_t addr, uint8_t val) {
	uint8_t data[] = {addr, val};
	spi_tx(spi_channel, data, 2);
}

void display_setup() {
	spi_channel = spi_setup_channel(1 << DISP_SS);

	cmd(0xc, 0x1); // zapnout
	cmd(0xb, 0x6); 
	cmd(0xa, 0xf); // intenzita
}

void display_show(uint8_t a, uint8_t b, uint8_t c) {
	for (int digit = 0; digit < 7; digit++) {
		uint8_t val = 0;
		val |= (font[c] >> digit) & 1;
		val |= ((font[b] >> digit) & 1) << 1;
		val |= ((font[a] >> digit) & 1) << 2;
		PIND |= (1 << PD4);
		cmd(digit + 1, val);
		PIND |= (1 << PD4);
	}
}
