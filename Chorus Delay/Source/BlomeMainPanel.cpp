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
    
    mTopPanel = std::make_unique<BlomeTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mTopPanel);
    
    mInputGainPanel = std::make_unique<BlomeGainPanel>(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    addAndMakeVisible(*mInputGainPanel);
    
    mOutputGainPanel = std::make_unique<BlomeGainPanel>(inProcessor);
    mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(*mOutputGainPanel);
    
    mCenterPanel = std::make_unique<BlomeCenterPanel>(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(*mCenterPanel);
}

BlomeMainPanel::~BlomeMainPanel()
{
    
}
