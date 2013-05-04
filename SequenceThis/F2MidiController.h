//
//  F2MidiController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2MidiController__
#define __SequenceThis__F2MidiController__

#include "WProgram.h"

class F2MidiController
{
private:
public:
    F2MidiController();
    ~F2MidiController();
    static F2MidiController* sharedInstance();
    void noteOn(unsigned int channel, unsigned int pitch, unsigned int velocity);
};

#endif /* defined(__SequenceThis__F2MidiController__) */
