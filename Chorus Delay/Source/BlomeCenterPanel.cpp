/*
  ==============================================================================

    BlomeCenterPanel.cpp
    Created: 11 Feb 2023 2:38:00pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeCenterPanel.h"

BlomeCenterPanel::BlomeCenterPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);
    
    mMenuBar = std::make_unique<BlomeCenterPanelMenuBar>(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar.get());
    
    mFXPanel = std::make_unique<BlomeFXPanel>(inProcessor);
    mFXPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mFXPanel.get());
    
    mMenuBar->addFXTypeComboBoxListener(mFXPanel.get());
}

BlomeCenterPanel::~BlomeCenterPanel()
{
    mMenuBar->removeFXTypeComboBoxListener(mFXPanel.get());
}
