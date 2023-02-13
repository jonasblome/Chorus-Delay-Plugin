/*
  ==============================================================================

    BlomeCenterPanelMenuBar.h
    Created: 11 Feb 2023 2:38:16pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"
#include "BlomeParameterComboBox.h"

class BlomeCenterPanelMenuBar
:   public BlomePanelBase
{
public:
    BlomeCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeCenterPanelMenuBar() override;
    
    void addFXTypeComboBoxListener(juce::ComboBox::Listener* inListener);
    void removeFXTypeComboBoxListener(juce::ComboBox::Listener* inListener);
    
private:
    std::unique_ptr<BlomeParameterComboBox> mFxTypeComboBox;
    
};
