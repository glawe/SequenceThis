//
//  F2Sequencer.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2SequenceController.h"

static F2SequenceController *_sharedInstance;

F2SequenceController* F2SequenceController::sharedInstance()
{
    if(_sharedInstance == 0)
        _sharedInstance = new F2SequenceController();
    return _sharedInstance;
}

F2SequenceController::F2SequenceController()
{
    _bpm = 120;
    for(byte i = 0; i < MAX_NUMBER_OF_PATTERNS; i++)
    {
        _patterns[i] = new F2SequencePattern();
    }
    _currentPatternNumber = 0;
}

F2SequenceController::~F2SequenceController()
{
    delete[] _patterns;
    delete _sharedInstance;
}

F2SequencePattern* F2SequenceController::getCurrentPattern()
{
    return _patterns[_currentPatternNumber];
}

void F2SequenceController::setCurrentPatternNumber(unsigned int number)
{
    _currentPatternNumber = number;
}

unsigned int F2SequenceController::getCurrentPatternNumber()
{
    return _currentPatternNumber;
}

byte F2SequenceController::getBpm()
{
    return _bpm;
}

void F2SequenceController::setBpm(byte bpm)
{
    _bpm = bpm;
}

