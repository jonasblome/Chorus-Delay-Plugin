/*
  ==============================================================================

 BlomeNoiseOverlayPanel.cpp
    Created: 29 May 2023 10:48:54am
    Author:  Jonas Blome

  ==============================================================================
*/

#include "BlomeNoiseOverlayPanel.h"

BlomeNoiseOverlayPanel::BlomeNoiseOverlayPanel(ChorusDelayAudioProcessor* inProcessor)
:   BlomePanelBase(inProcessor)
{
    setInterceptsMouseClicks(false, true);
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    mNoiseOverlay = juce::ImageCache::getFromMemory(BinaryData::noisetexture750x300_png, BinaryData::noisetexture750x300_pngSize);
    mNoiseOverlay.multiplyAllAlphas(0.065);
}

BlomeNoiseOverlayPanel::~BlomeNoiseOverlayPanel()
{
    
}

void BlomeNoiseOverlayPanel::paint(juce::Graphics& g)
{
    BlomePanelBase::paint(g);
    g.drawImage(mNoiseOverlay, getLocalBounds().toFloat());
}
