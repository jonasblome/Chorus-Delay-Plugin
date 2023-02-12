/*
  ==============================================================================

    BlomeMainPanel.h
    Created: 11 Feb 2023 2:37:50pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"
#include "BlomeTopPanel.h"
#include "BlomeGainPanel.h"
#include "BlomeCenterPanel.h"

class BlomeMainPanel
:   public BlomePanelBase
{
public:
    BlomeMainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeMainPanel();
    
private:
    std::unique_ptr<BlomeTopPanel> mTopPanel;
    std::unique_ptr<BlomeGainPanel> mInputGainPanel;
    std::unique_ptr<BlomeGainPanel> mOutputGainPanel;
    std::unique_ptr<BlomeCenterPanel> mCenterPanel;
};
