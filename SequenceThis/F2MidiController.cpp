//
//  F2MidiController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2MidiController.h"

static F2MidiController *_sharedInstance;

F2MidiController::F2MidiController()
{
}

F2MidiController::~F2MidiController()
{
    delete _sharedInstance;
}

F2MidiController* F2MidiController::sharedInstance()
{
    if(_sharedInstance = 0)
        _sharedInstance = new F2MidiController();
    return _sharedInstance;
}

void F2MidiController::noteOn(unsigned int channel, unsigned int pitch, unsigned int velocity)
{
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write(velocity);
}