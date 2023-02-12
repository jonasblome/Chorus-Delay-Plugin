/*
  ==============================================================================

    BlomeGainPanel.cpp
    Created: 11 Feb 2023 2:38:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeGainPanel.h"

BlomeGainPanel::BlomeGainPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

BlomeGainPanel::~BlomeGainPanel()
{
    
}
