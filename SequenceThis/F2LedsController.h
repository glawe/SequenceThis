//
//  F2LedsController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2LedsController__
#define __SequenceThis__F2LedsController__

#include "Arduino.h"
#include "Wire.h"

class F2LedsController
{
private:
public:
    F2LedsController();
    ~F2LedsController();
    static F2LedsController* sharedInstance();
    void endableStepLedWithNumber(byte number);
    void enableEditLedWithNumber(byte number);
    void stop();
};

#endif /* defined(__SequenceThis__F2LedsController__) */
