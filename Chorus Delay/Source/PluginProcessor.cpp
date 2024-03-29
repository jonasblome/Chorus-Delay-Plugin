/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BlomeParameters.h"

//==============================================================================
ChorusDelayAudioProcessor::ChorusDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters(*this, nullptr, juce::Identifier("PARAMETERS"), createParameterLayout())
#endif
{
    initializeDSP();
    
    mPresetManager = std::make_unique<BlomePresetManager>(this);
}

ChorusDelayAudioProcessor::~ChorusDelayAudioProcessor()
{
}

//==============================================================================
const juce::String ChorusDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChorusDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChorusDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChorusDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChorusDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChorusDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChorusDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChorusDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChorusDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChorusDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChorusDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for(int c = 0; c < 2; c++)
    {
        mDelay[c]->setSampleRate(sampleRate);
        mLFO[c]->setSampleRate(sampleRate);
        mFilter[c]->setSampleRate(sampleRate);
        mFilter[c]->prepareFilter(*parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterCutoff]), mFilterType, samplesPerBlock);
    }
}

void ChorusDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for(int i = 0; i < 2; i++)
    {
        mDelay[i]->reset();
        mLFO[i]->reset();
        if (mFilterActivated)
        {
            mFilter[i]->reset();
        }
        
        juce::zeromem(mFilteredSignalBuffer[i], sizeof(double) * maxBufferSize);
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChorusDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChorusDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        mInputGain[channel]->process(channelData,
                                *parameters.getRawParameterValue(BlomeParameterID[kParameter_InputGain]),
                                channelData,
                                buffer.getNumSamples());
        
        if (mFilterActivated)
        {
            mFilter[channel]->process(channelData,
                                      mFilteredSignalBuffer[channel],
                                      buffer.getNumSamples());
        }
        else
        {
            std::memcpy(mFilteredSignalBuffer[channel], channelData, buffer.getNumSamples() * sizeof(*channelData));
        }
        
        float rate = (channel == 0) ? 0.0f : (float)*parameters.getRawParameterValue(BlomeParameterID[kParameter_ModulationRate]);
        
        mLFO[channel]->process(rate,
                               *parameters.getRawParameterValue(BlomeParameterID[kParameter_ModulationDepth]),
                               buffer.getNumSamples());
        
        mDelay[channel]->process(channelData,
                                 mFilteredSignalBuffer[channel],
                                 *parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayTime]),
                                 *parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayFeedback]),
                                 *parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayWetDry]),
                                 *parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayType]),
                                 mLFO[channel]->getBuffer(),
                                 channelData,
                                 buffer.getNumSamples());
        
        mOutputGain[channel]->process(channelData,
                                      *parameters.getRawParameterValue(BlomeParameterID[kParameter_OutputGain]),
                                      channelData,
                                      buffer.getNumSamples());
    }
}

//==============================================================================
bool ChorusDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChorusDelayAudioProcessor::createEditor()
{
    return new ChorusDelayAudioProcessorEditor (*this);
}

//==============================================================================
void ChorusDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::XmlElement preset("Blome_StateInfo");
    juce::XmlElement* presetBody = new juce::XmlElement("Blome_Preset");
    
    mPresetManager->getXmlForPreset(presetBody);
    
    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

void ChorusDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::XmlElement xmlState = *getXmlFromBinary(data, sizeInBytes);
    juce::XmlElement* xmlStatePtr = &xmlState;
    
    if(xmlStatePtr)
    {
        for (auto* child: xmlStatePtr->getChildIterator())
        {
            mPresetManager->loadPresetForXml(*child);
        }
    }
    else
    {
        jassertfalse;
    }
}

float ChorusDelayAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
    
    return normalizeddB;
}

float ChorusDelayAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
    
    return normalizeddB;
}

juce::AudioProcessorValueTreeState::ParameterLayout ChorusDelayAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int p = 0; p < kParameter_TotalNumParameters; ++p)
    {
        layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter> (juce::ParameterID(BlomeParameterID[p], 1),
                                                                                    BlomeParameterLabels[p],
                                                                                    BlomeParameterRanges[p],
                                                                                    BlomeParameterDefaultValues[p]));
    }

    return layout;
}

void ChorusDelayAudioProcessor::updateFilter(float inCutoffFreq)
{
    if (mFilterActivated)
    {
        for(int c = 0; c < getTotalNumInputChannels(); c++)
        {
            mFilter[c]->updateFilter(inCutoffFreq, mFilterType, getBlockSize());
        }
    }
}

void ChorusDelayAudioProcessor::toggleFilterActivated()
{
    mFilterActivated = !mFilterActivated;
}

void ChorusDelayAudioProcessor::setFilterType(BlomeFilterType inFilterType)
{
    mFilterType = inFilterType;
    updateFilter(*parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterCutoff]));
}

void ChorusDelayAudioProcessor::initializeDSP()
{
    mFilterActivated = true;
    mFilterType = kBlomeFilterType_Bandpass;
    
    for(int i = 0; i < 2; i++)
    {
        mInputGain[i] = std::make_unique<BlomeGain>();
        mOutputGain[i] = std::make_unique<BlomeGain>();
        mDelay[i] = std::make_unique<BlomeDelay>();
        mLFO[i] = std::make_unique<BlomeLFO>();
        mFilter[i] = std::make_unique<BlomeFilter>();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChorusDelayAudioProcessor();
}
