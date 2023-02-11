/*
  ==============================================================================

    BlomeDelay.h
    Created: 8 Feb 2023 11:31:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomeAudioHelper.h"

class BlomeDelay
{
public:
    BlomeDelay();
    ~BlomeDelay();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inAudio,
                 float inTime,
                 float inFeedback,
                 float inWetDry,
                 float* inModulationBuffer,
                 float* outAudio,
                 int inNumSamplesToRender);


private:
    /** internal */
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    double mSampleRate;
    double mBuffer[maxBufferSize];
    double mFeedbackSample;
    
    int mDelayIndex;
};
