/*
  ==============================================================================

    BlomeMainPanel.cpp
    Created: 11 Feb 2023 2:37:50pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeMainPanel.h"

BlomeMainPanel::BlomeMainPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
}

BlomeMainPanel::~BlomeMainPanel()
{
    
}
