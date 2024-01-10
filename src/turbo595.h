/*******************************************************************************
* turbo595 is a library to allow extremely fast communication with 74xx595 Shift
* Registers, using chASM2 to control the hardware layer.
*
* v1.0
* 27 Aug 2023
* ADBeta 
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef TURBO595_H
#define TURBO595_H

#include <Arduino.h>
#include "chASM2.h"

typedef struct {
	chasm_t p_SCLK, p_RCLK, p_DAT;
} turbo595_t;

/** Initialization ************************************************************/
//Initializes the chasm_t structs and sets up the pins
//SCLK, RCLK, DAT
void turbo595_init(turbo595_t*, uint8_t, uint8_t, uint8_t);

/** Write functions *******************************************************/
//Write 8bits to the Shift Register.
void turbo595_write8(turbo595_t*, uint8_t);

//Write 16bits to the Shift Register.
void turbo595_write16(turbo595_t*, uint16_t);

//Write 32bits to the Shift Register.
void turbo595_write32(turbo595_t*, uint32_t);

//Write an array of arbitrary size to the Shift Register.
void turbo595_write_array(turbo595_t*, uint8_t* arr, uint16_t n);

#endif
#ifdef __cplusplus
}
#endif
