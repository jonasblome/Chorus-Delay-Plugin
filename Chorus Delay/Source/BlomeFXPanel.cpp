/*
  ==============================================================================

    BlomeFXPanel.cpp
    Created: 11 Feb 2023 2:38:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeFXPanel.h"

BlomeFXPanel::BlomeFXPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor),
    mStyle(kBlomeFXPanelStyle_Delay)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
}

BlomeFXPanel::~BlomeFXPanel()
{
    
}

void BlomeFXPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    
    switch (mStyle) {
        case kBlomeFXPanelStyle_Delay:
            g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            break;
        case kBlomeFXPanelStyle_Chorus:
            g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            break;
        default:
        case kBlomeFXPanelStyle_TotalNumStyles:
            g.drawFittedText("ERROR", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            jassertfalse;
            break;
    }
}

void BlomeFXPanel::setFXPanelStyle(BlomeFXPanelStyle inStyle)
{
    mStyle = inStyle;
}
