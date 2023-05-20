/*
  ==============================================================================

    BlomeDelay.cpp
    Created: 8 Feb 2023 11:31:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeDelay.h"
#include "JuceHeader.h"
#include "BlomeAudioHelpers.h"

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

void BlomeDelay::process(float* inAudioRaw,
                         float* inAudioFiltered,
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
    const float feedbackMapped = juce::jmap<float>(inFeedback, 0.0f, 1.0f, 0.0f, 1.2f);
    
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
        
        mBuffer[mDelayIndex] = tanh_clip(inAudioFiltered[i] + (mFeedbackSample * feedbackMapped));
        
        mFeedbackSample = sample;
        
        outAudio[i] = inAudioRaw[i] * dry + sample * wet;
        
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
    
    int index_y0 = (int) readPosition - 2;
    
    if(index_y0 < 0.0f) {
        index_y0 += maxBufferSize;
    }
    
    int index_y1 = (int) readPosition - 1;
    
    if(index_y1 < 0.0f) {
        index_y1 += maxBufferSize;
    }
    
    int index_y2 = (int) readPosition;
    
    if(index_y2 >= maxBufferSize) {
        index_y2 -= maxBufferSize;
    }
    
    int index_y3 = (int) readPosition + 1;
    
    if(index_y3 >= maxBufferSize) {
        index_y3 -= maxBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float sample_y2 = mBuffer[index_y2];
    const float sample_y3 = mBuffer[index_y3];
    const float t = readPosition - (int)readPosition;
    
//    double outSample = blome_linear_interp(sample_y1, sample_y2, t);
    double outSample = blome_cubic_interp(new float[] {sample_y0, sample_y1, sample_y2, sample_y3}, t);
    
    return outSample;
}
