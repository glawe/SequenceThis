//
//  F2SequencePattern.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2SequencePattern.h"

F2SequencePattern::F2SequencePattern()
{
    _nextStep = -1;
    _currentStepNumber = 0;
    for(byte i = 0; i < MAX_NUMBER_OF_STEPS; i++)
    {
        _steps[i] = new F2SequencerStep();
        _steps[i]->setNote(0x3A+i);
        _steps[i]->setVelocity(0x45);
    }
}

F2SequencePattern::~F2SequencePattern()
{
    delete[] _steps;
}

F2SequencerStep* F2SequencePattern::getNextStep()
{
    _nextStep = _nextStep + 1;
    F2SequencerStep *currentStep = _steps[_nextStep];
    _currentStepNumber = _nextStep;
    if(_currentStepNumber == 15)
        _nextStep = -1;
    return currentStep;
}

F2SequencerStep* F2SequencePattern::getStep(unsigned int stepNumber)
{
    return _steps[stepNumber];
}

F2SequencerStep* F2SequencePattern::getCurrentStep()
{
    return _steps[_currentStepNumber];
}

unsigned int F2SequencePattern::getCurrentStepNumber()
{
    return _currentStepNumber;
}

void F2SequencePattern::stop()
{
    _currentStepNumber = 0;
    _nextStep = -1;
}