/*
  ==============================================================================

    BlomeGainPanel.h
    Created: 11 Feb 2023 2:38:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"

class BlomeGainPanel
:   public BlomePanelBase
{
public:
    BlomeGainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeGainPanel();
    
private:
    
};
