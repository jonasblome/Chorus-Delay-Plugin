/*
  ==============================================================================

    BlomeParameterToggleButton.cpp
    Created: 17 May 2023 8:49:08pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeParameterToggleButton.h"

BlomeParameterToggleButton::BlomeParameterToggleButton(juce::AudioProcessorValueTreeState& stateToControl,
                                                       const juce::String& parameterID,
                                                       const juce::String& parameterLabel)
:   juce::ToggleButton(parameterLabel)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(stateToControl, parameterID, *this);
}

BlomeParameterToggleButton::~BlomeParameterToggleButton()
{
}
