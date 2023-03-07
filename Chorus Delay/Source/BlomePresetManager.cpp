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
    auto& parameters = mProcessor->getParameters();
    
    for(int i = 0; i < parameters.size(); i++) {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        inElement->setAttribute(parameter->paramID, parameter->getValue());
    }
}

void BlomePresetManager::loadPresetForXml(juce::XmlElement inElement)
{
    mCurrentPresetXml = &inElement;
    
    auto& parameters = mProcessor->getParameters();
    
    for(int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++) {
        const juce::String paramID = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(paramID);
        
        for(int j = 0; j < parameters.size(); j++) {
            juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);

            if(parameter->paramID == paramID) {
                parameter->setValueNotifyingHost(value);
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
    auto& parameters = mProcessor->getParameters();
    
    for(int i = 0; i < parameters.size(); i++) {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        const float defaultValue = parameter->getDefaultValue();
        parameter->setValueNotifyingHost(defaultValue);
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
