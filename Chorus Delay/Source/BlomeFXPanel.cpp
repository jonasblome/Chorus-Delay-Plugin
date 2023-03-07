/*
  ==============================================================================

    BlomeFXPanel.cpp
    Created: 11 Feb 2023 2:38:27pm
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeFXPanel.h"
#include "BlomeParameters.h"
#include "BlomeHelperFunctions.h"

BlomeFXPanel::BlomeFXPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    
    const int currentStyle = (int)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_DelayType]);
    setFXPanelStyle((BlomeFXPanelStyle)currentStyle);
}

BlomeFXPanel::~BlomeFXPanel()
{
    
}

void BlomeFXPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    juce::String label;

    switch (mStyle) {
        case kBlomeFXPanelStyle_Delay:
            label = "DELAY";
            break;
        case kBlomeFXPanelStyle_Chorus:
            label = "CHORUS";
            break;
        default:
        case kBlomeFXPanelStyle_TotalNumStyles:
            jassertfalse;
    }
    
    g.setColour(BlomeColour_5);
    g.setFont(font_3);
    
    g.drawText(label, 0, 0, getWidth(), 80, juce::Justification::centred);
    
    // Paint labels
    for(int i = 0; i < mSliders.size(); i++) {
        paintComponentLabel(g, mSliders[i]);
    }
}

void BlomeFXPanel::setFXPanelStyle(BlomeFXPanelStyle inStyle)
{
    mStyle = inStyle;
    
    mSliders.clear();
    
    const int slider_size = 56;
    int x = 130;
    int y = getHeight() * 0.5 - slider_size * 0.5;
    
    switch (mStyle) {
        case kBlomeFXPanelStyle_Delay: {
            BlomeParameterSlider* time = new BlomeParameterSlider(mProcessor->parameters,
                                                                  BlomeParameterID[kParameter_DelayTime],
                                                                  BlomeParameterLabels[kParameter_DelayTime]);
            time->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*time);
            mSliders.add(time);
            x = x + slider_size * 2;
            
            BlomeParameterSlider* feedback = new BlomeParameterSlider(mProcessor->parameters,
                                                                      BlomeParameterID[kParameter_DelayFeedback],
                                                                      BlomeParameterLabels[kParameter_DelayFeedback]);
            feedback->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*feedback);
            mSliders.add(feedback);
            x = x + slider_size * 2;
            
            BlomeParameterSlider* wetdry = new BlomeParameterSlider(mProcessor->parameters,
                                                                    BlomeParameterID[kParameter_DelayWetDry],
                                                                    BlomeParameterLabels[kParameter_DelayWetDry]);
            wetdry->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*wetdry);
            mSliders.add(wetdry);
            break;
            }
        case kBlomeFXPanelStyle_Chorus: {
            BlomeParameterSlider* rate = new BlomeParameterSlider(mProcessor->parameters,
                                                                  BlomeParameterID[kParameter_ModulationRate],
                                                                  BlomeParameterLabels[kParameter_ModulationRate]);
            rate->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*rate);
            mSliders.add(rate);
            x = x + slider_size * 2;
            
            BlomeParameterSlider* depth = new BlomeParameterSlider(mProcessor->parameters,
                                                                   BlomeParameterID[kParameter_ModulationDepth],
                                                                   BlomeParameterLabels[kParameter_ModulationDepth]);
            depth->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*depth);
            mSliders.add(depth);
            x = x + slider_size * 2;
            
            BlomeParameterSlider* wetdry = new BlomeParameterSlider(mProcessor->parameters,
                                                                    BlomeParameterID[kParameter_DelayWetDry],
                                                                    BlomeParameterLabels[kParameter_DelayWetDry]);
            wetdry->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(*wetdry);
            mSliders.add(wetdry);
            break;
        }
        default:
        case kBlomeFXPanelStyle_TotalNumStyles: {
            jassertfalse;
            break;
        }
    }
    
    repaint();
}

void BlomeFXPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    BlomeFXPanelStyle style = (BlomeFXPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();
    
    setFXPanelStyle(style);
}
