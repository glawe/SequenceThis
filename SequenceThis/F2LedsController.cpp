//
//  F2LedsController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2LedsController.h"
#define LED_STEP_CHIP_ADDRESS 0x21
#define LED_UTL_CHIP_ADDRESS 0x22

static F2LedsController *_sharedInstance;

F2LedsController* F2LedsController::sharedInstance()
{
    if(_sharedInstance == 0)
        _sharedInstance = new F2LedsController();
    return _sharedInstance;
}

F2LedsController::F2LedsController()
{
    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    Wire.send(0x00);
    Wire.send(0x00); 
    Wire.endTransmission();
    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    Wire.send(0x01); 
    Wire.send(0x00);
    Wire.endTransmission();
    Wire.beginTransmission(LED_UTL_CHIP_ADDRESS);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.endTransmission();
}

F2LedsController::~F2LedsController()
{
    delete _sharedInstance;
}

void F2LedsController::enableEditLedWithNumber(byte number)
{
    Wire.beginTransmission(LED_UTL_CHIP_ADDRESS);
    Wire.send(0x13);
    Wire.send(0x00);
    switch (number)
    { //TODO bitshift
        case 0:
            Wire.send(16);
            break;
        case 1:
            Wire.send(32);
            break;
        case 2:
            Wire.send(64);
            break;
        case 3:
            Wire.send(128);
            break;
        default:
            break;
    }
    
    Wire.endTransmission();
}

void F2LedsController::endableStepLedWithNumber(byte number)
{
    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    if(number <= 7)
    {
        Wire.send(0x13);
        Wire.send(0x00);
        Wire.endTransmission();
    }
    else
    {
        Wire.send(0x12);
        Wire.send(0x00);
        Wire.endTransmission();
    }
    Wire.endTransmission();
    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    if(number <= 7)
    {   
        Wire.send(0x12); //enable bank a
    }
    else
    {
        Wire.send(0x13); //enable bank b
    }
    switch (number)
    {
        case 0:
            Wire.send(1);
            break;
        case 1:
            Wire.send(2);
            break;
        case 2:
            Wire.send(4);
            break;
        case 3:
            Wire.send(8);
            break;
        case 4:
            Wire.send(16);
            break;
        case 5:
            Wire.send(32);
            break;
        case 6:
            Wire.send(64);
            break;
        case 7:
            Wire.send(128);
            break;
        case 8:
            Wire.send(1);
            break;
        case 9:
            Wire.send(2);
            break;
        case 10:
            Wire.send(4);
            break;
        case 11:
            Wire.send(8);
            break;
        case 12:
            Wire.send(16);
            break;
        case 13:
            Wire.send(32);
            break;
        case 14:
            Wire.send(64);
            break;
        case 15:
            Wire.send(128);
            break;
        default:
            break;
    }
    Wire.endTransmission();
}

void F2LedsController::stop()
{
    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    Wire.send(0x13);
    Wire.send(0x00);
    Wire.endTransmission();

    Wire.beginTransmission(LED_STEP_CHIP_ADDRESS);
    Wire.send(0x12);
    Wire.send(0x00);
    Wire.endTransmission();
}
