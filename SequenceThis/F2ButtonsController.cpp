//
//  F2ButtonsController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2ButtonsController.h"
#define LED_BUTTONS_CHIP_ADDRESS 0x20
#define UTL_BUTTONS_CHIP_ADDRESS 0x22

static F2ButtonsController *_sharedInstance;

F2ButtonsController* F2ButtonsController::sharedInstance()
{
    if (_sharedInstance == 0)
        _sharedInstance = new F2ButtonsController();
    return _sharedInstance;
}

F2ButtonsController::F2ButtonsController()
{
    //0x27 Step Leddar
    Wire.beginTransmission(LED_BUTTONS_CHIP_ADDRESS);
    Wire.send(0x13);
}

F2ButtonsController::~F2ButtonsController()
{
    delete _sharedInstance;
}

void F2ButtonsController::update()
{
    byte inputs=0;
    Wire.beginTransmission(LED_BUTTONS_CHIP_ADDRESS);
    Wire.send(0x12);
    Wire.endTransmission();
    Wire.requestFrom(LED_BUTTONS_CHIP_ADDRESS, 1); 
    inputs = Wire.receive();
    switch (inputs)
    {
        case 1:     //Button 1
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(0);
            break;
        case 2:     //Button 2
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(1);
            break;
        case 4:     //Button 3
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(2);
            break;
        case 8:    //Button 4
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(3);
            break;
        case 16:   //Button 5
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(4);
            break;
        case 32:  //Button 6
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(5);
            break;
        case 64:  //Button 7
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(6);
            break;
        case 128: //Button 8
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(7);
            break;
        default:
            break;
    }
    
    inputs=0;
    Wire.beginTransmission(LED_BUTTONS_CHIP_ADDRESS);
    Wire.send(0x13);
    Wire.endTransmission();
    Wire.requestFrom(LED_BUTTONS_CHIP_ADDRESS, 1);
    inputs = Wire.receive();
    switch (inputs)
    {
        case 1:     //Button 9
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(8);
            break;
        case 2:     //Button 10
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(9);
            break;
        case 4:     //Button 11
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(10);
            break;
        case 8:    //Button 12
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(11);
            break;
        case 16:   //Button 13
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(12);
            break;
        case 32:  //Button 14
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(13);
            break;
        case 64:  //Button 15
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(14);
            break;
        case 128: //Button 16
            F2ButtonsController::sharedInstance()->_callbackForStepButtons(15);
            break;
        default:
            break;
    }
    
    inputs = 0;
    Wire.beginTransmission(UTL_BUTTONS_CHIP_ADDRESS);
    Wire.send(0x13);
    Wire.endTransmission();
    Wire.requestFrom(UTL_BUTTONS_CHIP_ADDRESS, 1);
    inputs = Wire.receive();
    switch (inputs)
    {
        case 1:     //Button 1
        {
            if(_playStopButtonLastState != inputs)
            {
                F2ButtonsController::sharedInstance()->_callbackForPlayStopButton();
                _playStopButtonLastState = inputs;
            }
            break;
        }
        case 2:     //Button 2
            if(_exitButtonLastState != inputs)
            {
                _callbackForExitButton();
                _exitButtonLastState = inputs;
            }
            break;
        case 4:     //Button 3
            break;
        case 8:    //Button 4
            break;
        case 16:   //Button 5
            if(_editButtonsLastState[0] != inputs)
            {
                _callbackForEditButtons(0);
                _editButtonsLastState[0] = inputs;
            }
            break;
        case 32:  //Button 6
            if(_editButtonsLastState[1] != inputs)
            {
                _callbackForEditButtons(1);
                _editButtonsLastState[1] = inputs;
            }
            break;
        case 64:  //Button 7
            if(_editButtonsLastState[2] != inputs)
            {
                _callbackForEditButtons(2);
                _editButtonsLastState[2] = inputs;
            }       break;
        case 128: //Button 8
            if(_editButtonsLastState[3] != inputs)
            {
                _callbackForEditButtons(3);
                _editButtonsLastState[3] = inputs;
            }   break;
        default:
        {
            _playStopButtonLastState = 0;
            _exitButtonLastState = 0;
            for(int i = 0; i < 4; i++)
                _editButtonsLastState[i] = 0;
            break;
        }
    }
}

void F2ButtonsController::setCallbackForExitButton(void(*callbackExitButton)(void))
{
    _callbackForExitButton = callbackExitButton;
}

void F2ButtonsController::setCallbackForEditButtons(void(*callbackEditButtons)(byte))
{
    _callbackForEditButtons = callbackEditButtons;
}

void F2ButtonsController::setCallbackForPlayStopButton(void(*callbackPlayStopButton)(void))
{
    _callbackForPlayStopButton = callbackPlayStopButton;
}

void F2ButtonsController::setCallbackForStepButtons(void(*callbackStepButtons)(byte))
{
    _callbackForStepButtons = callbackStepButtons;
}



