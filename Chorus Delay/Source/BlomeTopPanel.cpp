/*
  ==============================================================================

    BlomeTopPanel.cpp
    Created: 11 Feb 2023 2:39:11pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeTopPanel.h"

BlomeTopPanel::BlomeTopPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH,
            TOP_PANEL_HEIGHT);
    
    int button_x = 15;
    int button_y = 10;
    int button_w = 55;
    int button_h = 25;
    
    mNewPreset = std::make_unique<juce::TextButton>();
    mNewPreset->setButtonText("NEW");
    mNewPreset->setBounds(button_x, button_y, button_w, button_h);
    mNewPreset->addListener(this);
    addAndMakeVisible(*mNewPreset);
    button_x = button_x + button_w;
    
    mSavePreset = std::make_unique<juce::TextButton>();
    mSavePreset->setButtonText("SAVE");
    mSavePreset->setBounds(button_x, button_y, button_w, button_h);
    mSavePreset->addListener(this);
    addAndMakeVisible(*mSavePreset);
    button_x = button_x + button_w;
    
    mSaveAsPreset = std::make_unique<juce::TextButton>();
    mSaveAsPreset->setButtonText("SAVE AS");
    mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
    mSaveAsPreset->addListener(this);
    addAndMakeVisible(*mSaveAsPreset);
    button_x = button_x + button_w;
    
    const int comboBox_w = 200;
    const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;
    
    mPresetDisplay = std::make_unique<juce::ComboBox>();
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(*mPresetDisplay);
    
    updatePresetComboBox();
}
BlomeTopPanel::~BlomeTopPanel()
{
    
}

void BlomeTopPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    
    g.drawFittedText("BLOME AUDIO PLUGIN", 0, 0, getWidth() - 10, getHeight(), juce::Justification::centredRight, 1);
}

void BlomeTopPanel::buttonClicked (juce::Button* b)
{
    BlomePresetManager* presetManager = mProcessor->getPresetManager();
    
    if(b == &*mNewPreset) {
        presetManager->createNewPreset();
    }
    else if (b == &*mSavePreset) {
        presetManager->savePreset();
    }
    else if (b == &*mSaveAsPreset) {
        displaySaveAsPopup();
    }
}

void BlomeTopPanel::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    
}

void BlomeTopPanel::displaySaveAsPopup()
{
    BlomePresetManager* presetManager = mProcessor->getPresetManager();
    
    juce::String currentPresetName = presetManager->getCurrentPresetName();
    
    juce::AlertWindow window("Save As", "Please enter a name for your Preset", juce::AlertWindow::NoIcon);
    
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("presetName", currentPresetName, "preset name: ");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);
    
    if(window.showAsync(<#const MessageBoxOptions &options#>, <#ModalComponentManager::Callback *callback#>)) {
        juce::String presetName = window.getTextEditor("presetName")->getText();
        presetManager->saveAsPreset(presetName);
    }
}

void BlomeTopPanel::updatePresetComboBox()
{
    BlomePresetManager* presetManager = mProcessor->getPresetManager();
    juce::String presetName = presetManager->getCurrentPresetName();
    
    mPresetDisplay->clear(juce::dontSendNotification);
    
    const int numPresets = presetManager->getNumberOfPresets();
    
    for(int i = 0; i < numPresets; i++) {
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i + 1));
    }
}
