#include <turbo595.h>

#define SCLK 8
#define RCLK 9
#define DAT 10

turbo595_t SR;

void setup() 
{
	//Initialize the shift register
	turbo595_init(&SR, SCLK, RCLK, DAT);
}

void loop() {
	//Emulate a blink demo with the SR
	turbo595_write_byte(&SR, 0xff);
	delay(1000);
	
	turbo595_write_byte(&SR, 0x00);
	delay(1000);
}
