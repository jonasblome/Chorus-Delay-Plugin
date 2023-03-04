/*
  ==============================================================================

    BlomeTopPanel.h
    Created: 11 Feb 2023 2:39:11pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"

class BlomeTopPanel
:   public BlomePanelBase,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    BlomeTopPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeTopPanel();
    
    void paint(juce::Graphics& g) override;
    
    void buttonClicked (juce::Button*) override;
    
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    
private:
    void displaySaveAsPopup();
    
    void updatePresetComboBox();
    
    std::unique_ptr<juce::ComboBox> mPresetDisplay;
    
    std::unique_ptr<juce::TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
};
