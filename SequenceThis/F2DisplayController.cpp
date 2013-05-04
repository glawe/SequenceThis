//
//  F2DisplayController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/16/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2DisplayController.h"

char* PROGMEM NOTES[0x78] = { "C -1", "C#-1", "D -1", "Eb-1", "E -1", "F -1", "F#-1", "G -1", "G#-1", "A -1", "Bb-1", "B -1", "C  0", "C# 0", "D  0", "Eb 0", "E  0", "F  0", "F# 0", "G  0", "G# 0", "A  0", "Bb 0", "B  0", "C  1", "C# 1", "D  1", "Eb 1", "E  1", "F  1", "F# 1", "G  1", "G# 1", "A  1", "Bb 1", "B  1", "C  2", "C# 2", "D  2", "Eb 2", "E  2", "F  2", "F# 2", "G  2", "G# 2", "A  2", "Bb 2", "B  2", "C  3", "C# 3", "D  3", "Eb 3", "E  3", "F  3", "F# 3", "G  3", "G# 3", "A  3", "Bb 3", "B  3", "C  4", "C# 4", "D  4", "Eb 4", "E  4", "F  4", "F# 4", "G  4", "G# 4", "A  4", "Bb 4", "B  4", "C  5", "C# 5", "D  5", "Eb 5", "E  5", "F  5", "F# 5", "G  5", "G# 5", "A  5", "Bb 5", "B  5", "C  6", "C# 6", "D  6", "Eb 6", "E  6", "F  6", "F# 6", "G  6", "G# 6", "A  6", "Bb 6", "B  6", "C  7", "C# 7", "D  7", "Eb 7", "E  7", "F  7", "F# 7", "G  7", "G# 7", "A  7", "Bb 7", "B  7", "C  8", "C# 8", "D  8", "Eb 8", "E  8", "F  8", "F# 8", "G  8", "G# 8", "A  8", "Bb 8", "B  8"};

byte CHARNOTE[8] =
{
    B00010,
    B00011,
    B00010,
    B00010,
    B01110,
    B11110,
    B01100,
};

byte CHARCLOCK[8] =
{
    B00000,
    B01110,
    B10101,
    B10111,
    B10001,
    B01110,
    B00000,
};

byte CHARARROWRIGHT[8] =
{
    B00000,
    B01000,
    B01100,
    B01110,
    B01100,
    B01000,
    B00000,
};

byte CHARVELOCITY[8] =
{
    B00000,
    B00001,
    B00011,
    B00111,
    B01111,
    B11111,
    B11111,
};

static F2DisplayController *_sharedInstance;

F2DisplayController* F2DisplayController::sharedInstance()
{
    if(_sharedInstance == 0)
    {
        _sharedInstance = new F2DisplayController();
    }
    return _sharedInstance;
}

F2DisplayController::F2DisplayController()
{
    _currentMode = 0;
    _currentEditStepNumber = 0;
    _lcd = new LiquidCrystal(12, 11, 5, 4, 3, 2);
    _lcd->createChar(0, CHARNOTE);
    _lcd->createChar(1, CHARCLOCK);
    _lcd->createChar(2, CHARVELOCITY);
    _lcd->begin(20, 4);
}

F2DisplayController::~F2DisplayController()
{
    delete _lcd;
    delete _sharedInstance;
}

//enum MENU { SONG = 0, STEPEDIT = 1, PATTERNEDIT = 2, SETTINGS = 3};
void F2DisplayController::setMode(byte mode)
{
    _currentMode = mode;
}

void F2DisplayController::setCurrentEditStepNumber(byte currentEditStepNumber)
{
    _currentEditStepNumber = currentEditStepNumber;
}

void F2DisplayController::update()
{
    switch (_currentMode)
    {
        case 0:
        {
            String step = "S:";
            step = step + (_currentEditStepNumber+1);
            _lcd->setCursor(0, 0);
            _lcd->print(step);
            
            _lcd->setCursor(0, 1);
            _lcd->write(byte(0));
            _lcd->setCursor(1, 1);
            _lcd->print(NOTES[_currentNote]);
            
            _lcd->setCursor(0, 2);
            _lcd->write(byte(1));
            _lcd->setCursor(1, 2);
            _lcd->print(_currentBpm);
            
            String mem = "Mem:";
            mem = mem + F2UtilityController::sharedInstance()->getAvailableMemory();
            _lcd->setCursor(0, 3);
            _lcd->print(mem);
            break;
        }
        case 1: //STEPEDIT
        {
            //Step
            _lcd->setCursor(0, 0);
            _lcd->write(byte(1));
            _lcd->setCursor(1, 0);
            _lcd->print(_currentEditStepNumber+1);
            
            
            //Note
            unsigned int editNote = F2SequenceController::sharedInstance()->getCurrentPattern()->getStep(_currentEditStepNumber)->getNote();
            _lcd->setCursor(4, 0);
            _lcd->write(byte(0));
            _lcd->setCursor(5, 0);
            _lcd->print(NOTES[editNote]);
            
            
            unsigned int editVelocity = F2SequenceController::sharedInstance()->getCurrentPattern()->getStep(_currentEditStepNumber)->getVelocity();
            _lcd->setCursor(10, 0);
            _lcd->write(byte(2));
            _lcd->setCursor(11, 0);
            //_lcd->print("   ");
            _lcd->setCursor(11, 0);
            _lcd->print(editVelocity);
            break;
        }
        default:
            break;
    }
}

void F2DisplayController::clear()
{
    _lcd->clear();
}

void F2DisplayController::setCurrentNote(unsigned int note)
{
    _currentNote = note;
}

void F2DisplayController::setCurrentBpm(byte bpm)
{
    _currentBpm = bpm;
}