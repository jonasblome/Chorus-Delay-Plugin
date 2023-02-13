/*
  ==============================================================================

    BlomeParameterComboBox.cpp
    Created: 13 Feb 2023 4:13:39pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeParameterComboBox.h"

BlomeParameterComboBox::BlomeParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID)
:   juce::ComboBox(parameterID)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, parameterID, *this);
}

BlomeParameterComboBox::~BlomeParameterComboBox()
{
    
}
