//
//  F2UtilityController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/20/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2UtilityController__
#define __SequenceThis__F2UtilityController__

#include "WProgram.h"

class F2UtilityController
{
private:
public:
    F2UtilityController();
    ~F2UtilityController();
    static F2UtilityController* sharedInstance();
    int getAvailableMemory();
};

#endif /* defined(__SequenceThis__F2UtilityController__) */
