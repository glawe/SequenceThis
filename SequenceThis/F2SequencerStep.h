//
//  F2SequencerStep.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2SequencerStep__
#define __SequenceThis__F2SequencerStep__

#include "WProgram.h"

class F2SequencerStep
{
private:
public:
    byte _velocity;
    unsigned int _note;
    F2SequencerStep();
    ~F2SequencerStep();
    unsigned int getNote();
    void setNote(unsigned int note);
    byte getVelocity();
    void setVelocity(byte velocity);
};

#endif /* defined(__SequenceThis__F2SequencerStep__) */
