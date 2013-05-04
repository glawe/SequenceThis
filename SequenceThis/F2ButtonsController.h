//
//  F2ButtonsController.h
//  SequenceThis
//
//  Created by Fredrik Glawe on 4/17/13.
//  Copyright (c) 2013 Fredrik Glawe. All rights reserved.
//

#ifndef __SequenceThis__F2ButtonsController__
#define __SequenceThis__F2ButtonsController__

#include "WProgram.h"
#include "Wire.h"

class F2ButtonsController
{
private:
    byte _playStopButtonLastState;
    byte _editButtonsLastState[4];
    byte _exitButtonLastState;
public:
    F2ButtonsController();
    ~F2ButtonsController();
    static F2ButtonsController* sharedInstance();
    void update();
    
    void (*_callbackForEditButtons)(byte);
    void setCallbackForEditButtons(void(*callbackEditButtons)(byte));
    
    void (*_callbackForExitButton)(void);
    void setCallbackForExitButton(void(*callbackExitButton)(void));
    
    void (*_callbackForPlayStopButton)(void);
    void (*_callbackForStepButtons)(byte);
    
    void setCallbackForPlayStopButton(void(*callbackPlayStopButton)(void));
    void setCallbackForStepButtons(void(*callbackStepButton)(byte));
};

#endif /* defined(__SequenceThis__F2ButtonsController__) */
