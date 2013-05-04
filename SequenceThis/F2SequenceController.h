//
//  F2SequenceController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2SequenceController__
#define __SequenceThis__F2SequenceController__

#include "WProgram.h"
#include "F2SequencePattern.h"

#define MAX_NUMBER_OF_PATTERNS 16

class F2SequenceController
{
private:
    F2SequencePattern *_patterns[MAX_NUMBER_OF_PATTERNS];
    unsigned int _currentPatternNumber;
    unsigned int _bpm;
public:
    F2SequenceController();
    ~F2SequenceController();
    static F2SequenceController* sharedInstance();
    F2SequencePattern* getCurrentPattern();
    void setCurrentPatternNumber(unsigned int number);
    unsigned int getCurrentPatternNumber();
    byte getBpm();
    void setBpm(byte bpm);
};

#endif /* defined(__SequenceThis__F2SequenceController__) */
