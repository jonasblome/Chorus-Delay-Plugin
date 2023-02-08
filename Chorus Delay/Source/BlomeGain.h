/*
  ==============================================================================

    BlomeGain.h
    Created: 8 Feb 2023 11:31:32pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

class BlomeGain
{
public:
    BlomeGain();
    ~BlomeGain();
    
    void process(float* inAudio,
                 float inGain,
                 float* outAudio,
                 int inNumSamplesToRender);
private:
};
