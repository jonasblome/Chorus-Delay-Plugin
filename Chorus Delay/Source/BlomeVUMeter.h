/*
  ==============================================================================

    BlomeVUMeter.h
    Created: 7 Mar 2023 12:44:51pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"

class BlomeVUMeter
:   public juce::Component,
    public juce::Timer
{
public:
    BlomeVUMeter(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeVUMeter();
    
    void paint(juce::Graphics& g) override;
    
    void timerCallback() override;
    
    void setParameterID(int inParameterID);
    
private:
    int mParameterID;
    
    float mCh0Level;
    float mCh1Level;
    
    ChorusDelayAudioProcessor* mProcessor;
};
