///
/// @file	LocalLibrary.h 
/// @brief	Library header
///
/// @details	<#details#>
/// @n	
/// @n @b	Project SequenceThis
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author	Fredrik Glawe
/// @author	Fredrik Glawe
/// @date	4/16/13 7:35 PM
/// @version	<#version#>
/// 
/// @copyright	© Fredrik Glawe, 2013
/// @copyright	CC = BY NC SA
///
/// @see	ReadMe.txt for references
///


// Core library - IDE-based
#if defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0x and 1.5x specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100)  // Arduino 23 specific
#include "WProgram.h"
#endif // end IDE

#ifndef SequenceThis_LocalLibrary_h
#define SequenceThis_LocalLibrary_h

///
/// @brief	Blink a LED
/// @details	LED attached to pin is light on then light off
/// @n		Total cycle duration = ms
/// @param	pin pin to which the LED is attached
/// @param	times number of times
/// @param	ms cycle duration in ms
///
void blink(uint8_t pin, uint8_t times, uint16_t ms);

#endif
