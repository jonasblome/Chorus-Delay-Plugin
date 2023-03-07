/*
  ==============================================================================

    BlomeInterfaceDefines.h
    Created: 11 Feb 2023 2:47:47pm
    Author:  Jonas Blome

  ==============================================================================
*/
#include "JuceHeader.h"

#pragma once

#define MAIN_PANEL_WIDTH                750
#define MAIN_PANEL_HEIGHT               300

#define TOP_PANEL_WIDTH                 MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT                45

#define GAIN_PANEL_WIDTH                100
#define GAIN_PANEL_HEIGHT               MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT

#define CENTER_PANEL_WIDTH              MAIN_PANEL_WIDTH - (GAIN_PANEL_WIDTH * 2)
#define CENTER_PANEL_HEIGHT             GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH     CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT    35

#define FX_PANEL_WIDTH                  CENTER_PANEL_WIDTH
#define FX_PANEL_HEIGHT                 CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT

const juce::Colour BlomeColour_1 = juce::Colour(105, 105, 105);
const juce::Colour BlomeColour_2 = juce::Colour(0, 0, 0).withAlpha(0.0f);
const juce::Colour BlomeColour_3 = juce::Colour(0, 0, 0).withAlpha(0.3f);
const juce::Colour BlomeColour_4 = juce::Colour(0, 0, 0).withAlpha(0.6f);
const juce::Colour BlomeColour_5 = juce::Colour(105, 105, 105).withAlpha(0.3f);
const juce::Colour BlomeColour_6 = juce::Colour(0, 0, 0).withAlpha(0.8f);
const juce::Colour BlomeColour_7 = juce::Colour(125, 125, 125);

const juce::Font font_1("Helvetica Neue", 12.00f, juce::Font::bold);
const juce::Font font_2("Helvetica Neue", 22.00f, juce::Font::bold);
const juce::Font font_3("Helvetica Neue", 48.00f, juce::Font::bold);
