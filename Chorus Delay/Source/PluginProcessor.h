/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "BlomeGain.h"
#include "BlomeDelay.h"
#include "BlomeLFO.h"
#include "BlomeFilter.h"
#include "BlomePresetManager.h"

//==============================================================================
/**
*/
class ChorusDelayAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ChorusDelayAudioProcessor();
    ~ChorusDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getInputGainMeterLevel(int inChannel);
    float getOutputGainMeterLevel(int inChannel);
    
    juce::AudioProcessorValueTreeState parameters;
    
    BlomePresetManager* getPresetManager()
    {
        return &*mPresetManager;
    }

private:
    // Internal
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void initializeDSP();
    
    std::unique_ptr<BlomeGain> mInputGain [2];
    std::unique_ptr<BlomeGain> mOutputGain [2];
    std::unique_ptr<BlomeDelay> mDelay [2];
    std::unique_ptr<BlomeLFO> mLFO [2];
    std::unique_ptr<BlomeFilter> mFilter [2];
    
    std::unique_ptr<BlomePresetManager> mPresetManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusDelayAudioProcessor)
};
