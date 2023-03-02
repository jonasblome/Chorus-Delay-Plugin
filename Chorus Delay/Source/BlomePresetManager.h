/*
  ==============================================================================

    BlomePresetManager.h
    Created: 14 Feb 2023 4:10:25pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".bpf"

class BlomePresetManager
{
public:
    BlomePresetManager(juce::AudioProcessor* inProcessor);
    ~BlomePresetManager();
    
    void getXmlForPreset(juce::XmlElement* inElement);
    
    void loadPresetForXml(juce::XmlElement inElement);
    
    int getNumberOfPresets();
    
    juce::String getPresetName(int inPresetIndex);
    
    void createNewPreset();
    
    void savePreset();
    
    void saveAsPreset(juce::String inPresetName);
    
    void loadPreset(int inPresetIndex);
    
    bool getIsCurrentPresetSaved();
    
    juce::String getCurrentPresetName();
    
private:
    void storeLocalPreset();
    
    bool mCurrentPresetIsSaved;
    
    juce::File mCurrentlyLoadedPreset;
    
    juce::Array<juce::File> mLocalPresets;
    
    juce::String mCurrentPresetName;
    
    juce::String mPresetDirectory;
    
    juce::XmlElement* mCurrentPresetXml;
    juce::AudioProcessor* mProcessor;
    
};
