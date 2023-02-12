/*
  ==============================================================================

    BlomeCenterPanelMenuBar.cpp
    Created: 11 Feb 2023 2:38:16pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeCenterPanelMenuBar.h"

BlomeCenterPanelMenuBar::BlomeCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
}

BlomeCenterPanelMenuBar::~BlomeCenterPanelMenuBar()
{
    
}
