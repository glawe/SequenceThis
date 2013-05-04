/// 
/// @mainpage	SequenceThis 
///
/// @details	<#details#>
/// @n 
/// @n 
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


///
/// @file	SequenceThis.ino 
/// @brief	Main sketch
///
/// @details	<#details#>
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
/// @n
///


// Core library for code-sense
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"   
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100) // Arduino 23 specific
#include "WProgram.h"
#else // error
#error Platform not defined
#endif

#include "Timer.h"
#include "Wire.h"
#include "F2DisplayController.h"
#include "F2RotaryController.h"
#include "F2LedsController.h"
#include "F2ButtonsController.h"
#include "F2MidiController.h"
#include "F2SequenceController.h"
#include "F2SequencerStep.h"
#include "F2UtilityController.h"

#define CHANGE_HEAP_SIZE(size)  __asm__ volatile ("\t.globl _min_heap_size\n\t.equ _min_heap_size, " #size "\n")
CHANGE_HEAP_SIZE(65536);

void editButtonsCallback(byte selection);
void stepButtonsCallback(byte buttonNumber);
void playStopButtonCallBack();
void exitButtonCallback();
void play();
void stop();
void rotaryCallbackUp();
void rotaryCallbackDown();
void update();
void setup();
void loop();

Timer _timer;
uint8_t _timerId;
byte _mode; //0 - Idle
byte _selectedStep;
byte _selectedEditPart; //Note:0 Velocity:1

bool _playing;

enum MENU { SONG, STEPEDIT, PATTERNEDIT, SETTINGS };

void update()
{
    F2SequencePattern *pattern = F2SequenceController::sharedInstance()->getCurrentPattern();
    F2SequencerStep *step = pattern->getNextStep();
    F2LedsController::sharedInstance()->endableStepLedWithNumber(pattern->getCurrentStepNumber());
    F2MidiController::sharedInstance()->noteOn(0x90, step->getNote(), step->getVelocity());
}

void setup()
{
    //Serial.begin(31250);
    Serial.begin(9600);
    _selectedEditPart = 0;
    Wire.begin();
    F2UtilityController::sharedInstance();
    F2DisplayController::sharedInstance();
    F2LedsController::sharedInstance();
    F2MidiController::sharedInstance();
    F2SequenceController::sharedInstance();
    F2ButtonsController::sharedInstance();
    F2ButtonsController::sharedInstance()->setCallbackForExitButton(exitButtonCallback);
    F2ButtonsController::sharedInstance()->setCallbackForPlayStopButton(playStopButtonCallBack);
    F2ButtonsController::sharedInstance()->setCallbackForStepButtons(stepButtonsCallback);
    F2RotaryController::sharedInstance()->setCallback(rotaryCallbackUp, rotaryCallbackDown);
    F2ButtonsController::sharedInstance()->setCallbackForEditButtons(editButtonsCallback);
    F2LedsController::sharedInstance()->enableEditLedWithNumber(0);
}

void loop()
{
    _timer.update();
    F2ButtonsController::sharedInstance()->update();
    switch(_mode)
    {
        case 0: //Idle
        {
            F2SequencePattern *currentPattern = F2SequenceController::sharedInstance()->getCurrentPattern();
            F2SequencerStep *currentStep = currentPattern->getCurrentStep();
            F2DisplayController::sharedInstance()->setCurrentBpm(F2SequenceController::sharedInstance()->getBpm());
            F2DisplayController::sharedInstance()->setCurrentNote(currentStep->getNote());
            F2DisplayController::sharedInstance()->update();
            break;
        }
    }
}

void play()
{
    long bpm = (6000/F2SequenceController::sharedInstance()->getBpm())*2;
    _timerId = _timer.every(bpm, update);
}

void stop()
{
    _timer.stop(_timerId);
    F2SequenceController::sharedInstance()->getCurrentPattern()->stop();
}

void playStopButtonCallBack()
{
    if(_playing)
    {
        stop();
        F2LedsController::sharedInstance()->stop();
        _playing = false;
    }
    else
    {
        play();
        _playing = true;
    }
}

void editButtonsCallback(byte selection)
{
    _selectedEditPart = selection;
    F2LedsController::sharedInstance()->enableEditLedWithNumber(_selectedEditPart);
}

void exitButtonCallback()
{
    F2DisplayController::sharedInstance()->clear();
    F2DisplayController::sharedInstance()->setCurrentEditStepNumber(_selectedStep);
    F2DisplayController::sharedInstance()->setMode(0);
}

void stepButtonsCallback(byte buttonNumber)
{
    _selectedStep = buttonNumber;
    F2DisplayController::sharedInstance()->clear();
    F2DisplayController::sharedInstance()->setCurrentEditStepNumber(_selectedStep);
    F2DisplayController::sharedInstance()->setMode(1);
}

void rotaryCallbackUp()
{
    Serial.print("Up");
    switch (_selectedEditPart)
    {
        case 0:
            F2SequenceController::sharedInstance()->getCurrentPattern()->_steps[_selectedStep]->_note++;
            break;
        case 1:
            F2SequenceController::sharedInstance()->getCurrentPattern()->_steps[_selectedStep]->_velocity++;
            break;
        default:
            break;
    }
}

void rotaryCallbackDown()
{
    Serial.print("down");
    switch (_selectedEditPart)
    {
        case 0:
            F2SequenceController::sharedInstance()->getCurrentPattern()->_steps[_selectedStep]->_note--;
            break;
        case 1:
            F2SequenceController::sharedInstance()->getCurrentPattern()->_steps[_selectedStep]->_velocity--;
            break;
        default:
            break;
    }
}



