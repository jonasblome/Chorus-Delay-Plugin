/*
  ==============================================================================

    BlomeFXPanel.h
    Created: 11 Feb 2023 2:38:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"

enum BlomeFXPanelStyle
{
    kBlomeFXPanelStyle_Delay,
    kBlomeFXPanelStyle_Chorus,
    kBlomeFXPanelStyle_TotalNumStyles
};

class BlomeFXPanel
:   public BlomePanelBase
{
public:
    BlomeFXPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeFXPanel();
    
    void paint(juce::Graphics& g) override;
    
    void setFXPanelStyle(BlomeFXPanelStyle inStyle);
    
private:
    BlomeFXPanelStyle mStyle;
    
};
