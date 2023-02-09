/*
  ==============================================================================

    BlomeGain.cpp
    Created: 8 Feb 2023 11:31:32pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeGain.h"

#include "JuceHeader.h"

BlomeGain::BlomeGain()
{
    
}
BlomeGain::~BlomeGain()
{
    
}

void BlomeGain::process(float* inAudio,
             float inGain,
             float* outAudio,
             int inNumSamplesToRender)
{
    // Mapping gain value to decibel scale
    float gainMapped = juce::jmap<float>(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
    gainMapped = juce::Decibels::decibelsToGain(gainMapped, -24.0f);
    
    for(int i = 0; i < inNumSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * gainMapped;
    }
}
