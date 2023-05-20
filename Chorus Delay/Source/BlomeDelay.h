/*
  ==============================================================================

    BlomeDelay.h
    Created: 8 Feb 2023 11:31:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomeAudioHelpers.h"

enum BlomeDelayType
{
    kBlomeDelayType_Delay = 0,
    kBlomeDelayType_Chorus,
};

class BlomeDelay
{
public:
    BlomeDelay();
    ~BlomeDelay();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inAudioRaw,
                 float* inAudioFiltered,
                 float inTime,
                 float inFeedback,
                 float inWetDry,
                 float inType,
                 float* inModulationBuffer,
                 float* outAudio,
                 int inNumSamplesToRender);


private:
    /** internal */
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    double mSampleRate;
    double mBuffer[maxBufferSize];
    double mFeedbackSample;
    
    float mTimeSmoothed;
    
    int mDelayIndex;
};
