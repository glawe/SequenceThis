//
//  F2UtilityController.cpp
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/20/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#include "F2UtilityController.h"

static F2UtilityController *_sharedInstance;

F2UtilityController* F2UtilityController::sharedInstance()
{
    if(_sharedInstance == 0)
        _sharedInstance = new F2UtilityController();
    return _sharedInstance;
}


F2UtilityController::F2UtilityController()
{
    
}

F2UtilityController::~F2UtilityController()
{
    delete _sharedInstance;
}

int F2UtilityController::getAvailableMemory()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}