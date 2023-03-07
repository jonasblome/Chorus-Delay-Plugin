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
    const int h = 20;
    
    const float cornerSize = 3.0f;
    
    const juce::String label = inComponent->getName();
    
    g.setColour(BlomeColour_3);
    g.fillRoundedRectangle(x, y, w, h, cornerSize);
    
    g.setColour(BlomeColour_1);
    g.setFont(font_1);
    
    g.drawFittedText(label, x, y, w, h, juce::Justification::centred, 1);
}
