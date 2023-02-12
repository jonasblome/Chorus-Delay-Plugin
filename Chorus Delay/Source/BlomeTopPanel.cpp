/*
  ==============================================================================

    BlomeTopPanel.cpp
    Created: 11 Feb 2023 2:39:11pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeTopPanel.h"

BlomeTopPanel::BlomeTopPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}
BlomeTopPanel::~BlomeTopPanel()
{
    
}

void BlomeTopPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    
    g.drawFittedText("BLOME AUDIO PLUGIN", 0, 0, getWidth() - 10, getHeight(), juce::Justification::centredRight, 1);
}
