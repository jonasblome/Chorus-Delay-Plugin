/*
  ==============================================================================

    BlomeGain.cpp
    Created: 8 Feb 2023 11:31:32pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeGain.h"

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
    for(int i = 0; i < inNumSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * inGain;
    }
}
