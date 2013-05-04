//
//  F2RotaryController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/16/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2RotaryController.h"

F2RotaryController *_sharedInstance;
byte _encoderPin1;
byte _encoderPin2;
volatile long _encoderValue;
unsigned char _encoderPin1Value;
unsigned char _encoderPin2Value;
unsigned char _encoderPreviousValue = 0;
const byte _stepAmount = 1;

F2RotaryController* F2RotaryController::sharedInstance()
{
    if(_sharedInstance == 0)
        _sharedInstance = new F2RotaryController();
    return _sharedInstance;
}

int oldnumber;
volatile int number;                    // used in both interrupt routines
volatile boolean halfleft = false;      // Used in both interrupt routines
volatile boolean halfright = false;     // Used in both interrupt routines

void isr_A()
{                                           // A went LOW
    delay(3);                                             // Debounce time
    // Trade off bounce vs missed counts
    int bits = PORTB;                                     // Atomic read of encoder inputs
    int LSB = (bits >> 2) & 0x01;
    int MSB = (bits >> 4) & 0x01;
    
    if(LSB == LOW)
    {                              		// A still LOW ?
        if(MSB == HIGH && halfright == false)
        {     		// -->
            halfright = true;                                 // One half click clockwise
        }
        if(MSB == LOW && halfleft == true)
        {        		// <--
            halfleft = false;                                 // One whole click counter-
            number--;                                         // clockwise
        }
    }
    Serial.print(number);
}
void isr_B()
{                                           // B went LOW
    delay(3);                                             // Debounce time
    // Trade off bounce vs missed counts
    int bits = PORTB;                                     // Atomic read of encoder inputs
    int LSB = (bits >> 2) & 0x01;
    int MSB = (bits >> 4) & 0x01;
    
    if(MSB == LOW)
    {                              		// A still LOW ?
        if(LSB == HIGH && halfleft == false)
        {     		// <--
            halfleft = true;                                  // One half  click counter-
        }                                                   // clockwise
        if(LSB == LOW && halfright == true)
        {       		// -->
            halfright = false;                                // One whole click clockwise
            number++;
        }
    }
    Serial.print(number);
}


F2RotaryController::F2RotaryController()
{
    _encoderPin1 = 7;
    _encoderPin2 = 6;
    _encoderValue = 0;
    
    pinMode(_encoderPin1, INPUT);
    pinMode(_encoderPin2, INPUT);
    
    digitalWrite(_encoderPin1, HIGH);
    digitalWrite(_encoderPin2, HIGH);
    
    //attachInterrupt(0, updateEncoder, CHANGE);
    //attachInterrupt(1, updateEncoder, CHANGE);

    attachInterrupt(0, isr_A, FALLING);   		// Call isr_2 when digital pin 2 goes LOW
    attachInterrupt(1, isr_B, FALLING);          // Call isr_3 when digital pin 3 goes LOW
    
    //attachInterrupt(0, updateEncoder, FALLING);
    //attachInterrupt(1, updateEncoder, RISING);

}

F2RotaryController::~F2RotaryController()
{
    delete _sharedInstance;
}

void F2RotaryController::setCallback(void (*callbackUp)(void), void (*callbackDown)(void))
{
    _callbackUp = callbackUp;
    _callbackDown = callbackDown;
}

void F2RotaryController::updateEncoder()
{
    _encoderPin1Value = digitalRead(_encoderPin1);
    _encoderPin2Value = digitalRead(_encoderPin2);
    if((!_encoderPin1Value) && (_encoderPreviousValue))
    {
        if(_encoderPin2Value)
        {
            _encoderValue -= _stepAmount;
            F2RotaryController::sharedInstance()->_callbackDown();
        }
        else
        {
            _encoderValue += _stepAmount;
            F2RotaryController::sharedInstance()->_callbackUp();
        }
    }
    _encoderPreviousValue = _encoderPin1Value;
}

long F2RotaryController::getCurrentValue()
{
    return _encoderValue;
}
