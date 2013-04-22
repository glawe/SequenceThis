//
//  F2SequencerStep.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2SequencerStep.h"

F2SequencerStep::F2SequencerStep()
{
    _note = 0;
    _velocity = 0;
}

F2SequencerStep::~F2SequencerStep()
{
}

unsigned int F2SequencerStep::getNote()
{
    return _note;
}

void F2SequencerStep::setNote(unsigned int note)
{
    _note = note;
}

byte F2SequencerStep::getVelocity()
{
    return _velocity;
}

void F2SequencerStep::setVelocity(byte velocity)
{
    _velocity = velocity;
}