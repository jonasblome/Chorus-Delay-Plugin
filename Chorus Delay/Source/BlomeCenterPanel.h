/*
  ==============================================================================

    BlomeCenterPanel.h
    Created: 11 Feb 2023 2:38:00pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"
#include "BlomeCenterPanelMenuBar.h"
#include "BlomeFXPanel.h"

class BlomeCenterPanel
:   public BlomePanelBase
{
public:
    BlomeCenterPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeCenterPanel();
    
private:
    std::unique_ptr<BlomeCenterPanelMenuBar> mMenuBar;
    std::unique_ptr<BlomeFXPanel> mFXPanel;
};
