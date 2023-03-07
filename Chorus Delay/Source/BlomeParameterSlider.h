/*
  ==============================================================================

    BlomeParameterSlider.h
    Created: 13 Feb 2023 4:13:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlomeParameterSlider
:   public juce::Slider
{
public:
    BlomeParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
                         const juce::String& parameterID,
                         const juce::String& parameterLabel);
    ~BlomeParameterSlider();
    
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlomeParameterSlider);
};
