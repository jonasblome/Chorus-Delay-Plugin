/*
  ==============================================================================

    BlomePresetManager.cpp
    Created: 14 Feb 2023 4:10:25pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomePresetManager.h"

#if JUCE_WINDOWS
    static const juce::String directorySeparator = "\\";
#elif JUCE_MAC
    static const juce::String directorySeparator = "/";
#endif

BlomePresetManager::BlomePresetManager(juce::AudioProcessor* inProcessor)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcessor)
{
    const juce::String pluginName = (juce::String) mProcessor->getName();
    
    mPresetDirectory =
    (juce::File::getSpecialLocation(juce::File::userDesktopDirectory)).getFullPathName() + directorySeparator + pluginName;
    
    if(!juce::File(mPresetDirectory).exists()) {
        juce::File(mPresetDirectory).createDirectory();
    }
    
    storeLocalPreset();
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

int BlomePresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

juce::String BlomePresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void BlomePresetManager::createNewPreset()
{
    const int numParameters = mProcessor->getParameters().size();
    
    for(int i = 0; i < numParameters; i++) {
        mProcessor->getParameters()[i]->setValueNotifyingHost(mProcessor->getParameters()[i]->getDefaultValue());
    }
    
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void BlomePresetManager::savePreset()
{
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    
    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                      destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void BlomePresetManager::saveAsPreset(juce::String inPresetName)
{
    juce::File presetFile = juce::File(mPresetDirectory + directorySeparator + inPresetName + PRESET_FILE_EXTENSION);
    
    if(!presetFile.exists()) {
        presetFile.create();
    }
    else {
        presetFile.deleteFile();
    }
    
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(),
                          destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;
    
    storeLocalPreset();
}

void BlomePresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];
    
    juce::MemoryBlock presetBinary;
    
    if(mCurrentlyLoadedPreset.loadFileAsData(presetBinary)) {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(), (int) presetBinary.getSize());
    }
}

bool BlomePresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

juce::String BlomePresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void BlomePresetManager::storeLocalPreset()
{
    mLocalPresets.clear();
    
    for(juce::DirectoryEntry entry : juce::RangedDirectoryIterator(juce::File(mPresetDirectory),
                                          false,
                                          "*" + (juce::String)PRESET_FILE_EXTENSION,
                                          juce::File::TypesOfFileToFind::findFiles))
    {
        juce::File preset = entry.getFile();
        mLocalPresets.add(preset);
    }
}
