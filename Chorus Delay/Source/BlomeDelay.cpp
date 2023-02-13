/*
  ==============================================================================

    BlomeDelay.cpp
    Created: 8 Feb 2023 11:31:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeDelay.h"
#include "JuceHeader.h"
#include "BlomeAudioHelper.h"

BlomeDelay::BlomeDelay()
:   mSampleRate(-1),
    mFeedbackSample(0.0),
    mTimeSmoothed(0),
    mDelayIndex(0)
{
    reset();
}
BlomeDelay::~BlomeDelay()
{
}

void BlomeDelay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void BlomeDelay::reset()
{
    mTimeSmoothed = 0.0f;
    juce::zeromem(mBuffer, sizeof(double) * maxBufferSize);
}

void BlomeDelay::process(float* inAudio,
             float inTime,
             float inFeedback,
             float inWetDry,
             float inType,
             float* inModulationBuffer,
             float* outAudio,
             int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = juce::jmap<float>(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);
    
    for(int i = 0; i< inNumSamplesToRender; i++) {
        if((int)inType == kBlomeDelayType_Delay) {
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
        }
        else {
            const double delayTimeModulation = 0.003 + (0.002 * inModulationBuffer[i]);
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
        }
        
        const double delayTimeInSamples = mTimeSmoothed * mSampleRate;
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
        
        mFeedbackSample = sample;
        
        outAudio[i] = inAudio[i] * dry + sample * wet;
        
        mDelayIndex++;
        
        if(mDelayIndex >= maxBufferSize) {
            mDelayIndex -= maxBufferSize;
        }
    }
}

double BlomeDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    
    if(readPosition < 0.0f) {
        readPosition += maxBufferSize;
    }
    
    int index_y0 = (int) readPosition - 1;
    
    if(index_y0 < 0.0f) {
        index_y0 += maxBufferSize;
    }
    
    int index_y1 = readPosition;
    
    if(index_y1 >= maxBufferSize) {
        index_y1 -= maxBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;
    
    double outSample = blome_linear_interp(sample_y0, sample_y1, t);
    
    return outSample;
}
