//
//  F2DisplayController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/16/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2DisplayController__
#define __SequenceThis__F2DisplayController__

#include <LiquidCrystal.h>
#include "WProgram.h"
#include "F2UtilityController.h"
#include "F2SequencerStep.h"
#include "F2SequenceController.h"
#include "F2SequencePattern.h"

class F2DisplayController
{
public:
    F2DisplayController();
    ~F2DisplayController();
    void update();
    void setMode(byte mode);
    void setCurrentNote(unsigned int note);
    void setCurrentEditStepNumber(byte stepNumber);
    static F2DisplayController* sharedInstance();
    void setCurrentBpm(byte bpm);
    void clear();
private:
    LiquidCrystal *_lcd;
    unsigned int _currentNote;
    byte _currentEditStepNumber;
    byte _currentBpm;
    byte _currentMode;
    F2SequencerStep *_currentEditStep;
};

#endif
