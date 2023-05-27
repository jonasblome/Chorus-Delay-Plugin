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
#define CENTER_PANEL_MENU_BAR_HEIGHT    20

#define FX_PANEL_WIDTH                  CENTER_PANEL_WIDTH
#define FX_PANEL_HEIGHT                 CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT

#define COMPONENT_LABEL_HEIGHT          20

// Light Gray
const juce::Colour BlomeColour_LightGray = juce::Colour(150, 150, 150);
const juce::Colour BlomeColour_LightGrayLightTransparent = juce::Colour(BlomeColour_LightGray).withAlpha(0.5f);

// Gray
const juce::Colour BlomeColour_Gray = juce::Colour(70, 70, 70);

// Dark Gray
const juce::Colour BlomeColour_DarkGray = juce::Colour(40, 40, 40);

// Black
const juce::Colour BlomeColour_Black = juce::Colour(0, 0, 0);
const juce::Colour BlomeColour_BlackFullTransparent = juce::Colour(BlomeColour_Black).withAlpha(0.0f);
const juce::Colour BlomeColour_BlackLightTransparent = juce::Colour(BlomeColour_Black).withAlpha(0.63f);
const juce::Colour BlomeColour_BlackMediumTransparent = juce::Colour(BlomeColour_Black).withAlpha(0.78f);
const juce::Colour BlomeColour_BlackStrongTransparent = juce::Colour(BlomeColour_Black).withAlpha(0.95f);

// Dark Yellow
const juce::Colour BlomeColour_DarkOrange = juce::Colour(138, 39, 0);
const juce::Colour BlomeColour_DarkOrangeStrongTransparent = juce::Colour(BlomeColour_DarkOrange).withAlpha(0.99f);

// Fonts
const juce::Font font_small_bold("Helvetica Neue", 12.00f, juce::Font::bold);
const juce::Font font_small_accentuated("Helvetica Neue", 12.30f, juce::Font::bold);
const juce::Font font_medium("Helvetica Neue", 22.00f, juce::Font::bold);
const juce::Font font_large("Helvetica Neue", 48.00f, juce::Font::bold);
