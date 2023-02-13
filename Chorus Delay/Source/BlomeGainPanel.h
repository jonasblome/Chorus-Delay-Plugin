/*
  ==============================================================================

    BlomeGainPanel.h
    Created: 11 Feb 2023 2:38:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"
#include "BlomeParameterSlider.h"

class BlomeGainPanel
:   public BlomePanelBase
{
public:
    BlomeGainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeGainPanel();
    
    void paint(juce::Graphics& g) override;
    
    void setParameterID(int inParameterID);
    
private:
    std::unique_ptr<BlomeParameterSlider> mSlider;
    
};
