/*
  ==============================================================================

    BlomeLFO.h
    Created: 8 Feb 2023 11:31:12pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomeAudioHelper.h"

class BlomeLFO
{
public:
    BlomeLFO();
    ~BlomeLFO();
    
    void reset();
    
    void setSampleRate(double inSampleRate);
    
    void process(float inRate, float inDepth, int inNumSamples);
    
    float* getBuffer();
private:
    double mSampleRate;
    
    float mPhase;
    
    float mBuffer[maxBufferSize];
};
