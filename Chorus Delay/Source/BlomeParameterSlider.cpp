/*
  ==============================================================================

    BlomeParameterSlider.cpp
    Created: 13 Feb 2023 4:13:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeParameterSlider.h"

BlomeParameterSlider::BlomeParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
                                           const juce::String& parameterID,
                                           const juce::String& parameterLabel)
:   juce::Slider(parameterLabel)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    
    setRange(0.0f, 1.0f, 0.001f);
    
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
}

BlomeParameterSlider::~BlomeParameterSlider()
{
    
}
