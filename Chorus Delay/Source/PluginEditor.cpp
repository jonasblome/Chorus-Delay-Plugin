/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusDelayAudioProcessorEditor::ChorusDelayAudioProcessorEditor (ChorusDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mMainPanel = std::make_unique<BlomeMainPanel>(&audioProcessor);
    addAndMakeVisible(mMainPanel.get());
    
    mLookAndFeel = std::make_unique<BlomeLookAndFeel>();
    setLookAndFeel(&*mLookAndFeel);
    
    juce::LookAndFeel::setDefaultLookAndFeel(&*mLookAndFeel);
}

ChorusDelayAudioProcessorEditor::~ChorusDelayAudioProcessorEditor()
{
}

//==============================================================================
void ChorusDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setColour(BlomeColour_DarkOrange);
    g.fillAll();
}

void ChorusDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
