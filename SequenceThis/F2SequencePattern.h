//
//  F2SequencePattern.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2SequencePattern__
#define __SequenceThis__F2SequencePattern__

#include "WProgram.h"
#include "F2SequencerStep.h"

#define MAX_NUMBER_OF_STEPS 16

class F2SequencePattern
{
private:
    unsigned int _currentStepNumber;
    unsigned int _nextStep;
public:
    F2SequencePattern();
    ~F2SequencePattern();
    F2SequencerStep* _steps[MAX_NUMBER_OF_STEPS];
    F2SequencerStep* getNextStep();
    F2SequencerStep* getCurrentStep();
    F2SequencerStep* getStep(unsigned int stepNumber);
    unsigned int getCurrentStepNumber();
    void stop();
};

#endif /* defined(__SequenceThis__F2SequencePattern__) */
