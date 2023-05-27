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
    
    g.setColour(BlomeColour_LightGrayLightTransparent);
    g.setFont(font_large);
    
    // Paint labels
    for(int i = 0; i < mSliders.size(); i++)
    {
        paintComponentLabel(g, mSliders[i]);
    }
}

void BlomeFXPanel::setFXPanelStyle(BlomeFXPanelStyle inStyle)
{
    mStyle = inStyle;
    
    mSliders.clear();
    mToggleButtons.clear();
    mComboBoxes.clear();
    
    const int slider_size = 56;
    const int toggleButton_size = 20;
    int x = 74;
    int y = getHeight() * 0.5 - slider_size * 0.75;
    
    switch (mStyle) {
        case kBlomeFXPanelStyle_Delay:
        {
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
            
            BlomeParameterSlider* cutoff = new BlomeParameterSlider(mProcessor->parameters,
                                                                   BlomeParameterID[kParameter_FilterCutoff],
                                                                   BlomeParameterLabels[kParameter_FilterCutoff]);
            x = x + slider_size * 2;
            
            cutoff->setBounds(x, y, slider_size, slider_size);
            cutoff->addListener(this);
            addAndMakeVisible(*cutoff);
            mSliders.add(cutoff);
            
            BlomeParameterComboBox* filterType = new BlomeParameterComboBox(mProcessor->parameters,
                                                                            BlomeParameterID[kParameter_FilterType]);
            
            x = x - slider_size * 0.25;
            y = y + slider_size + COMPONENT_LABEL_HEIGHT * 1.5;
            
            filterType->setBounds(x, y, slider_size * 1.5, toggleButton_size);
            filterType->addItem("Low", 1);
            filterType->addItem("High", 2);
            filterType->addItem("Band", 3);
            filterType->addListener(this);
            filterType->setSelectedItemIndex((int)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterType]), juce::dontSendNotification);
            addAndMakeVisible(*filterType);
            mComboBoxes.add(filterType);
            
            BlomeParameterToggleButton* filterToggle = new BlomeParameterToggleButton(mProcessor->parameters,
                                                                                      BlomeParameterID[kParameter_FilterActivated],
                                                                                      BlomeParameterLabels[kParameter_FilterActivated]);
            
            x = x + slider_size * 0.75 - toggleButton_size * 0.5;
            y = y + COMPONENT_LABEL_HEIGHT * 1.5;
            
            filterToggle->setBounds(x, y, toggleButton_size, toggleButton_size);
            filterToggle->addListener(this);
            filterToggle->setToggleState((bool)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterActivated]), juce::dontSendNotification);
            addAndMakeVisible(*filterToggle);
            mToggleButtons.add(filterToggle);
            
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
            
            BlomeParameterSlider* cutoff = new BlomeParameterSlider(mProcessor->parameters,
                                                                   BlomeParameterID[kParameter_FilterCutoff],
                                                                   BlomeParameterLabels[kParameter_FilterCutoff]);
            x = x + slider_size * 2;
            
            cutoff->setBounds(x, y, slider_size, slider_size);
            cutoff->addListener(this);
            addAndMakeVisible(*cutoff);
            mSliders.add(cutoff);
            
            BlomeParameterComboBox* filterType = new BlomeParameterComboBox(mProcessor->parameters,
                                                                            BlomeParameterID[kParameter_FilterType]);
            
            x = x - slider_size * 0.25;
            y = y + slider_size + COMPONENT_LABEL_HEIGHT * 1.5;
            
            filterType->setBounds(x, y, slider_size * 1.5, toggleButton_size);
            filterType->addItem("Low", 1);
            filterType->addItem("High", 2);
            filterType->addItem("Band", 3);
            filterType->addListener(this);
            filterType->setSelectedItemIndex((int)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterType]), juce::dontSendNotification);
            addAndMakeVisible(*filterType);
            mComboBoxes.add(filterType);
            
            BlomeParameterToggleButton* filterToggle = new BlomeParameterToggleButton(mProcessor->parameters,
                                                                                      BlomeParameterID[kParameter_FilterActivated],
                                                                                      BlomeParameterLabels[kParameter_FilterActivated]);
            
            x = x + slider_size * 0.75 - toggleButton_size * 0.5;
            y = y + COMPONENT_LABEL_HEIGHT * 1.5;
            
            filterToggle->setBounds(x, y, toggleButton_size, toggleButton_size);
            filterToggle->addListener(this);
            filterToggle->setToggleState((bool)*mProcessor->parameters.getRawParameterValue(BlomeParameterID[kParameter_FilterActivated]), juce::dontSendNotification);
            addAndMakeVisible(*filterToggle);
            mToggleButtons.add(filterToggle);
            
            break;
        }
        default:
        case kBlomeFXPanelStyle_TotalNumStyles:
        {
            jassertfalse;
            break;
        }
    }
    
    repaint();
}

void BlomeFXPanel::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == mComboBoxes.getUnchecked(0))
    {
        mProcessor->setFilterType((BlomeFilterType)comboBox->getSelectedItemIndex());
    }
    else if (comboBox->getName() == BlomeParameterID[kParameter_DelayType])
    {
        BlomeFXPanelStyle style = (BlomeFXPanelStyle)comboBox->getSelectedItemIndex();
        
        setFXPanelStyle(style);
    }
}

void BlomeFXPanel::sliderValueChanged (juce::Slider* slider)
{
    if(slider == mSliders.getUnchecked(3))
    {
        mProcessor->updateFilter(slider->getValue());
    }
}

void BlomeFXPanel::buttonClicked (juce::Button* button)
{
    if(button == mToggleButtons.getUnchecked(0))
    {
        mProcessor->toggleFilterActivated();
    }
}
