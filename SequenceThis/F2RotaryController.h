//
//  F2RotaryEncoder.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/16/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2RotaryController__
#define __SequenceThis__F2RotaryController__

#include "Arduino.h"

class F2RotaryController
{
private:
    static void updateEncoder();
public:
    F2RotaryController();
    ~F2RotaryController();
    static F2RotaryController* sharedInstance();
    void (*_callbackUp)(void);
    void (*_callbackDown)(void);
    long getCurrentValue();
    void setCallback(void(*callbackUp)(void), void(*callbackDown)(void));
};

#endif /* defined(__SequenceThis__F2RotaryController__) */
