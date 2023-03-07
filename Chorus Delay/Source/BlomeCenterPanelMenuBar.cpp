/*
  ==============================================================================

    BlomeCenterPanelMenuBar.cpp
    Created: 11 Feb 2023 2:38:16pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeCenterPanelMenuBar.h"
#include "BlomeParameters.h"

BlomeCenterPanelMenuBar::BlomeCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
    
    const int width = 85;
    
    mFxTypeComboBox = std::make_unique<BlomeParameterComboBox>(mProcessor->parameters, BlomeParameterID[kParameter_DelayType]);
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    mFxTypeComboBox->setSelectedItemIndex((int)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayType]), juce::dontSendNotification);
    addAndMakeVisible(mFxTypeComboBox.get());
}

BlomeCenterPanelMenuBar::~BlomeCenterPanelMenuBar()
{
    
}

void BlomeCenterPanelMenuBar::addFXTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}

void BlomeCenterPanelMenuBar::removeFXTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->removeListener(inListener);
}
