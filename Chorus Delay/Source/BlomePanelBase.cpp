/*
  ==============================================================================

    BlomePanelBase.cpp
    Created: 11 Feb 2023 2:37:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomePanelBase.h"
#include "BlomeInterfaceDefines.h"

BlomePanelBase::BlomePanelBase(ChorusDelayAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}

BlomePanelBase::~BlomePanelBase()
{
}

void BlomePanelBase::mouseEnter(const juce::MouseEvent& event)
{
    repaint();
}

void BlomePanelBase::mouseExit(const juce::MouseEvent& event)
{
    repaint();
}

void BlomePanelBase::paint(juce::Graphics& g)
{
}
