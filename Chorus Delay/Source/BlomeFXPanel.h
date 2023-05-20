/*
  ==============================================================================

    BlomeFXPanel.h
    Created: 11 Feb 2023 2:38:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "BlomePanelBase.h"
#include "BlomeParameterSlider.h"
#include "BlomeParameterToggleButton.h"
#include "BlomeParameterComboBox.h"

enum BlomeFXPanelStyle
{
    kBlomeFXPanelStyle_Delay,
    kBlomeFXPanelStyle_Chorus,
    kBlomeFXPanelStyle_TotalNumStyles
};

class BlomeFXPanel
:   public BlomePanelBase,
    public juce::ComboBox::Listener,
    public juce::Slider::Listener,
    public juce::Button::Listener
{
public:
    BlomeFXPanel(ChorusDelayAudioProcessor* inProcessor);
    ~BlomeFXPanel();
    
    void paint(juce::Graphics& g) override;
    
    void setFXPanelStyle(BlomeFXPanelStyle inStyle);
    
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    
    void buttonClicked (juce::Button* button) override;
    
private:
    BlomeFXPanelStyle mStyle;
    juce::OwnedArray<BlomeParameterSlider> mSliders;
    juce::OwnedArray<BlomeParameterToggleButton> mToggleButtons;
    juce::OwnedArray<BlomeParameterComboBox> mComboBoxes;
};
