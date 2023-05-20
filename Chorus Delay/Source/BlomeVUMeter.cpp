/*
  ==============================================================================

    BlomeVUMeter.cpp
    Created: 7 Mar 2023 12:44:51pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeVUMeter.h"
#include "BlomeInterfaceDefines.h"
#include "BlomeParameters.h"

BlomeVUMeter::BlomeVUMeter(ChorusDelayAudioProcessor* inProcessor)
:   mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    mProcessor(inProcessor)
{
    
}

BlomeVUMeter::~BlomeVUMeter()
{
    
}

void BlomeVUMeter::paint(juce::Graphics& g)
{
    const int meter_w = getWidth() / 3;
    
    g.setColour(BlomeColour_BlackMediumTransparent);
    const float cornerSize = 3.0f;
    
    // Left
    const juce::Rectangle<int> meter1 (0, 0, meter_w, getHeight());
    g.fillRoundedRectangle(meter1.toFloat(), cornerSize);
    
    // Right
    const juce::Rectangle<int> meter2 (meter_w * 2, 0, meter_w, getHeight());
    g.fillRoundedRectangle(meter2.toFloat(), cornerSize);
    
    int ch0Fill = getHeight() - (getHeight() * mCh0Level);
    int ch1Fill = getHeight() - (getHeight() * mCh1Level);
    
    if(ch0Fill < 0) {
        ch0Fill = 0;
    }
    if(ch1Fill < 0) {
        ch1Fill = 0;
    }
    
    g.setColour(BlomeColour_LightGray);
    g.fillRect(0, ch0Fill, meter_w, getHeight());
    g.fillRect(meter_w * 2, ch1Fill, meter_w, getHeight());
}

void BlomeVUMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;
    
    switch(mParameterID)
    {
        case kParameter_InputGain:
            updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getInputGainMeterLevel(1);
            break;
        case kParameter_OutputGain:
            updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);
            break;
    }
    
    if(updatedCh0Level > mCh0Level) {
        mCh0Level = updatedCh0Level;
    } else {
        mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
    }
    
    if(updatedCh1Level > mCh1Level) {
        mCh1Level = updatedCh1Level;
    } else {
        mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
    }
    
    mCh0Level = blome_denormalize(mCh0Level);
    mCh1Level = blome_denormalize(mCh1Level);
    
    if(mCh0Level && mCh1Level) {
        repaint();
    }
}


void BlomeVUMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    
    startTimer(15);
}
