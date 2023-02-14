/*
  ==============================================================================

    BlomePresetManager.h
    Created: 14 Feb 2023 4:10:25pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlomePresetManager
{
public:
    BlomePresetManager(juce::AudioProcessor* inProcessor);
    ~BlomePresetManager();
    
    void getXmlForPreset(juce::XmlElement inElement);
    
    void loadPresetForXml(juce::XmlElement inElement);
    
private:
    juce::XmlElement* mCurrentPresetXml;
    juce::AudioProcessor* mProcessor;
    
};
