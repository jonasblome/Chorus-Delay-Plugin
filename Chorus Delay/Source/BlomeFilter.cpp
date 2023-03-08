/*
  ==============================================================================

    BlomeFilter.cpp
    Created: 8 Mar 2023 9:10:39am
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeFilter.h"
#include "BlomeHelperFunctions.h"

BlomeFilter::BlomeFilter()
:   mSampleRate(-1)
{
    reset();
}

BlomeFilter::~BlomeFilter()
{
    
}

void BlomeFilter::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void BlomeFilter::reset()
{
    mFilter.reset();
    juce::zeromem(mBuffer, sizeof(double) * maxBufferSize);
}

void BlomeFilter::prepareFilter(float cutoffFreq,
                                BlomeFilterType inType,
                                int inNumSamplesToRender)
{
    juce::dsp::ProcessSpec spec({mSampleRate, (juce::uint32)inNumSamplesToRender, 1});
    
    if((int)inType == kBlomeFilterType_Lowpass) {
        mFilter.state = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(cutoffFreq,
                                                                                     spec.sampleRate,
                                                                                     2000,
                                                                                     juce::dsp::WindowingFunction<float>::blackman);
    }
    
    mFilter.prepare(spec);
}

void BlomeFilter::process(float* inAudio,
                          float inWetDry,
                          float* outAudio,
                          int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    
    std::memcpy(mBuffer, inAudio, inNumSamplesToRender * sizeof(*inAudio));
    
    float* const bufferPtr = mBuffer;
    
    juce::AudioBuffer<float> buffer(&bufferPtr, 1, inNumSamplesToRender);
    juce::AudioSourceChannelInfo channelInfo(buffer);
    juce::dsp::AudioBlock<float> block(*channelInfo.buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    mFilter.process(context);
    
    for(int i = 0; i < inNumSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * dry + mBuffer[i] * wet;
    }
}
