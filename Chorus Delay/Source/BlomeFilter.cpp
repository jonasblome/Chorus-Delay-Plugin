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
    
    switch (inType) {
        case kBlomeFilterType_Lowpass:
            mFilter.state = juce::dsp::IIR::Coefficients<float>::makeLowPass(mSampleRate,
                                                                             cutoffMapped,
                                                                             0.72f);
            break;
        case kBlomeFilterType_Highpass:
            mFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighPass(mSampleRate,
                                                                              cutoffMapped,
                                                                              0.72f);
            break;
        case kBlomeFilterType_Bandpass:
            mFilter.state = juce::dsp::IIR::Coefficients<float>::makeBandPass(mSampleRate,
                                                                              cutoffMapped,
                                                                              0.72f);
            break;
        default:
            break;
    }
    
    juce::dsp::ProcessSpec spec({mSampleRate, (juce::uint32)inNumSamplesToRender, 1});
    
    mFilter.prepare(spec);
}

void BlomeFilter::updateFilter(float inCutoffFreq,
                               BlomeFilterType inType,
                               int inNumSamplesToRender)
{
    const float cutoffMapped = juce::mapToLog10(inCutoffFreq, 20.0f, 20000.0f);
    
    switch (inType) {
        case kBlomeFilterType_Lowpass:
            *mFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeLowPass(mSampleRate,
                                                                                   cutoffMapped,
                                                                                   0.72f);
            break;
        case kBlomeFilterType_Highpass:
            *mFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeHighPass(mSampleRate,
                                                                                    cutoffMapped,
                                                                                    0.72f);
            break;
        case kBlomeFilterType_Bandpass:
            *mFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeBandPass(mSampleRate,
                                                                                    cutoffMapped,
                                                                                    0.72f);
            break;
        default:
            break;
    }
}

void BlomeFilter::process(float* inAudio,
                          float* outAudio,
                          int inNumSamplesToRender)
{
    std::memcpy(mBuffer, inAudio, inNumSamplesToRender * sizeof(*inAudio));
    
    float* const bufferPtr = mBuffer;
    
    juce::AudioBuffer<float> buffer(&bufferPtr, 1, inNumSamplesToRender);
    juce::AudioSourceChannelInfo channelInfo(buffer);
    juce::dsp::AudioBlock<float> block(*channelInfo.buffer, (size_t) channelInfo.startSample);
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    mFilter.process(context);
    
    for(int i = 0; i < inNumSamplesToRender; i++) {
        outAudio[i] = mBuffer[i];
    }
}
