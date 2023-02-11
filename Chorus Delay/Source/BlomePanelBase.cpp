/*
  ==============================================================================

    BlomePanelBase.cpp
    Created: 11 Feb 2023 2:37:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomePanelBase.h"

BlomePanelBase::BlomePanelBase(ChorusDelayAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}

BlomePanelBase::~BlomePanelBase()
{
    
}

void BlomePanelBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::whitesmoke);
    g.fillAll();
    
    g.setColour(juce::Colours::black);
    g.drawRect(1, 1, getWidth()-1, getHeight()-1, 2);
}
