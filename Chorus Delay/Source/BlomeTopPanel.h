/*
  ==============================================================================

    BlomeTopPanel.h
    Created: 11 Feb 2023 2:39:11pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"

class BlomeTopPanel
:   public BlomePanelBase
{
public:
    BlomeTopPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeTopPanel();
    
    void paint(juce::Graphics& g) override;
    
private:
    
};
