/*
  ==============================================================================

    BlomeFilter.h
    Created: 8 Mar 2023 9:10:39am
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "BlomeAudioHelpers.h"

enum BlomeFilterType
{
    kBlomeFilterType_Lowpass = 0,
    kBlomeFilterType_Highpass,
    kBlomeFilterType_Bandpass,
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
                 float* outAudio,
                 int inNumSamplesToRender);
    
private:
    double mSampleRate;
    float mCutoffFreq;
    float mBuffer[maxBufferSize];
    
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> mFilter;
};
