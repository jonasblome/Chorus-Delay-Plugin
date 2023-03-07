/*
  ==============================================================================

    BlomeGainPanel.cpp
    Created: 11 Feb 2023 2:38:42pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeGainPanel.h"
#include "BlomeParameters.h"
#include "BlomeHelperFunctions.h"

BlomeGainPanel::BlomeGainPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
    
    const int meter_w = 64;
    mVUMeter = std::make_unique<BlomeVUMeter>(inProcessor);
    mVUMeter->setBounds(getWidth() * 0.5 - (meter_w * 0.5),
                        (getHeight() * 0.55) - (meter_w * 0.5),
                        meter_w,
                        getHeight() * 0.45);
    addAndMakeVisible(*mVUMeter);
}

BlomeGainPanel::~BlomeGainPanel()
{
    
}

void BlomeGainPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    
    if(mSlider) {
        paintComponentLabel(g, mSlider.get());
    }
}

void BlomeGainPanel::setParameterID(int inParameterID)
{
    mSlider = std::make_unique<BlomeParameterSlider>(mProcessor->parameters, BlomeParameterID[inParameterID]);
    const int slider_size = 54;
    
    mSlider->setBounds(getWidth() * 0.5 - slider_size * 0.5,
                       getHeight() * 0.25 - slider_size * 0.5 - 10,
                       slider_size,
                       slider_size);
    addAndMakeVisible(mSlider.get());
    
    mVUMeter->setParameterID(inParameterID);
}
