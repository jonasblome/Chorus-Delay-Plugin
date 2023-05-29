/*
  ==============================================================================

 BlomeNoiseOverlayPanel.h
    Created: 29 May 2023 10:48:54am
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"

class BlomeNoiseOverlayPanel
:   public BlomePanelBase
{
public:
    // Constructors
    BlomeNoiseOverlayPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeNoiseOverlayPanel();
    
    // Methods
    void paint(juce::Graphics& g) override;
    
private:
    // Fields
    juce::Image mNoiseOverlay;
    
    // Methods
};
