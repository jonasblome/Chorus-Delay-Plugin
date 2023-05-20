/*
  ==============================================================================

    BlomeHelperFunctions.h
    Created: 13 Feb 2023 5:13:01pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "BlomeInterfaceDefines.h"

inline void paintComponentLabel(juce::Graphics& g, juce::Component* inComponent)
{
    const int x = inComponent->getX() - inComponent->getWidth() * 0.25;
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f;
    const int h = COMPONENT_LABEL_HEIGHT;
    
    const float cornerSize = 3.0f;
    
    const juce::String label = inComponent->getName();
    
    g.setColour(BlomeColour_BlackMediumTransparent);
    g.fillRoundedRectangle(x, y, w, h, cornerSize);
    
    g.setColour(BlomeColour_LightGray);
    g.setFont(font_small_bold);
    
    g.drawFittedText(label, x, y, w, h, juce::Justification::centred, 1);
}
