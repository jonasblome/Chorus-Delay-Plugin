/*
  ==============================================================================

    BlomeFilter.h
    Created: 8 Mar 2023 9:10:39am
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "BlomeAudioHelper.h"

enum BlomeFilterType
{
    kBlomeFilterType_Lowpass = 0,
    kBlomeFilterType_Bandpass,
    kBlomeFilterType_Highpass
};

class BlomeFilter
{
public:
    BlomeFilter();
    
    ~BlomeFilter();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void prepareFilter(float cutoffFreq,
                       BlomeFilterType inType,
                       int inNumSamplesToRender);
    
    void updateFilter(float cutoffFreq,
                       BlomeFilterType inType,
                       int inNumSamplesToRender);
    
    void process(float* inAudio,
                 float inWetDry,
                 float* outAudio,
                 int inNumSamplesToRender);
    
private:
    double mSampleRate;
    float mCutoffFreq;
    float mBuffer[maxBufferSize];
    
    juce::dsp::ProcessorDuplicator<juce::dsp::FIR::Filter<float>, juce::dsp::FIR::Coefficients<float>> mFilter;
};
