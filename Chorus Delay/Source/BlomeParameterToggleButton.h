/*
  ==============================================================================

    BlomeParameterToggleButton.h
    Created: 17 May 2023 8:49:08pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlomeParameterToggleButton
:   public juce::ToggleButton
{
public:
    BlomeParameterToggleButton(juce::AudioProcessorValueTreeState& stateToControl,
                               const juce::String& parameterID,
                               const juce::String& parameterLabel);
    ~BlomeParameterToggleButton();
    
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> mAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlomeParameterToggleButton);
};
