# turbo595
turbo595 is a library to send data to a 74xx595 Shift Register, using chASM2
as a hardware handler, which provides super high speed port manipulation.
See [chASM2](https://github.com/ADBeta/chASM2) for more information.

This library natively supports the ATTiny family of MCUs, as well as the Arduino
family; Tested on the Uno, Mega, Nano and ATTiny24

## Usage
To use the turbo595 library, create a struct and initialize it.  
```C
turbo595_t shift_reg;

turbo595_init(&shift_reg, 8, 9 , 10);
```

You can send 8, 16 or 32 bits (byte, int and long) by using these methods:
```C 
turbo595_write_byte(&shift_reg, byte); //Transmit 8 bits 
turbo595_write_int(&shift_reg, int);   //Transmit 16 bits  
turbo595_write_long(&shift_reg, long); //Transmit 32 bits  
```

You can also send an arbitrary number of bytes.  
```C
uint8_t array[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

turbo595_write_array(&shift_reg, 8, *array);
```

## TODO
* See if the speed of the functions exceed recommended speed for ICs.

## Changelog

--------------------------------------------------------------------------------
<b>(c) ADBeta 2023-2024</b>  
This software is under the GPL v2 licence. Please read the LICENCE file
