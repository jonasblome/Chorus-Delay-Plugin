/*
  ==============================================================================

    BlomeParameterComboBox.h
    Created: 13 Feb 2023 4:13:39pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlomeParameterComboBox
:   public juce::ComboBox
{
public:
    BlomeParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
                           const juce::String& parameterID);
    ~BlomeParameterComboBox();
    
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlomeParameterComboBox);
    
};
