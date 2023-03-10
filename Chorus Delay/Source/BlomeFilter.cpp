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

void BlomeFilter::prepareFilter(float inCutoffFreq,
                                BlomeFilterType inType,
                                int inNumSamplesToRender)
{
    const float cutoffMapped = juce::jmap<float>(inCutoffFreq, 0.0f, 1.0f, 20.0f, 20000.0f);
    
    juce::dsp::ProcessSpec spec({mSampleRate, (juce::uint32)inNumSamplesToRender, 1});
    
    if((int)inType == kBlomeFilterType_Lowpass) {
        mFilter.state = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(cutoffMapped,
                                                                                     spec.sampleRate,
                                                                                     200,
                                                                                     juce::dsp::WindowingFunction<float>::blackman);
    }
    
    mFilter.state->normalise();
    
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
        outAudio[i] = mBuffer[i];
    }
}
