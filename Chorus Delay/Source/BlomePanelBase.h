/*
  ==============================================================================

    BlomePanelBase.h
    Created: 11 Feb 2023 2:37:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "BlomeInterfaceDefines.h"

class BlomePanelBase
:   public juce::Component
{
public:
    BlomePanelBase(ChorusDelayAudioProcessor* inProcessor);
    ~BlomePanelBase();
    
    void mouseEnter(const juce::MouseEvent& event) override;
    
    void mouseExit(const juce::MouseEvent& event) override;
    
    void paint(juce::Graphics& g) override;
    
protected:
    ChorusDelayAudioProcessor* mProcessor;
};
