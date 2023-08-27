#include <turbo595.h>

#define SCLK 8
#define RCLK 9
#define DAT 10

turbo595_t SR;

//Create an array
uint8_t arr[4] = {0xde, 0xad, 0xbe, 0xef);

void setup()
{
	//Initialize the shift register
	turbo595_init(&SR, SCLK, RCLK, DAT);

	//Write the array to the SR
	turbo595_write_array(&SR, 4, arr);
}

void loop() 
{
}
