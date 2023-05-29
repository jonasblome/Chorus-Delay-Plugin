/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BlomeMainPanel.h"
#include "BlomeNoiseOverlayPanel.h"
#include "BlomeLookAndFeel.h"

//==============================================================================
/**
*/
class ChorusDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusDelayAudioProcessorEditor (ChorusDelayAudioProcessor&);
    ~ChorusDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChorusDelayAudioProcessor& audioProcessor;
    std::unique_ptr<BlomeMainPanel> mMainPanel;
    std::unique_ptr<BlomeNoiseOverlayPanel> mNoiseOverlayPanel;
    std::unique_ptr<BlomeLookAndFeel> mLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusDelayAudioProcessorEditor)
};
