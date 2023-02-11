/*
  ==============================================================================

    BlomeLFO.cpp
    Created: 8 Feb 2023 11:31:12pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeLFO.h"
#include "JuceHeader.h"

BlomeLFO::BlomeLFO()
{
    reset();
}
BlomeLFO::~BlomeLFO()
{
    
}

void BlomeLFO::reset()
{
    mPhase = 0.0f;
    juce::zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void BlomeLFO::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void BlomeLFO::process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = juce::jmap<float>(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
    
    for(int i = 0; i< inNumSamples; i++) {
        mPhase = mPhase + (rate / mSampleRate);
        
        if(mPhase > 1.0f) {
            mPhase -= 1.0f;
        }
        
        const float lfoPosition = sinf(k2PI * mPhase) * inDepth;
        mBuffer[i] = lfoPosition;
    }
}

float* BlomeLFO::getBuffer()
{
    return mBuffer;
}
