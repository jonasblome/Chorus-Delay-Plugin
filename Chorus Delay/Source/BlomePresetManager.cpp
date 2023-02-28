/*
  ==============================================================================

    BlomePresetManager.cpp
    Created: 14 Feb 2023 4:10:25pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomePresetManager.h"

BlomePresetManager::BlomePresetManager(juce::AudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}
BlomePresetManager::~BlomePresetManager()
{
    
}

void BlomePresetManager::getXmlForPreset(juce::XmlElement* inElement)
{
    const int numParameters = mProcessor->getParameters().size();
    
    for(int i = 0; i < numParameters; i++) {
        inElement->setAttribute(mProcessor->getParameters()[i]->getName(30), mProcessor->getParameters()[i]->getValue());
    }
}

void BlomePresetManager::loadPresetForXml(juce::XmlElement inElement)
{
    mCurrentPresetXml = &inElement;
    
    const int numParameters = mProcessor->getParameters().size();
    
    for(int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++) {
        const juce::String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);
        
        for(int j = 0; j < numParameters; j++) {
            if(mProcessor->getParameters()[j]->getName(30) == name) {
                mProcessor->getParameters()[j]->setValueNotifyingHost(value);
            }
        }
    }
}
