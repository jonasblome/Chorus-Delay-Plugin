/*
  ==============================================================================

    BlomeLookAndFeel.h
    Created: 7 Mar 2023 9:38:06am
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlomeLookAndFeel
:   public juce::LookAndFeel_V4
{
public:
    BlomeLookAndFeel()
    {
        //Store Image Assets
        mSliderImage = juce::ImageCache::getFromMemory(BinaryData::kadenze_knob_png,
                                                       BinaryData::kadenze_knob_pngSize);
        
        // ComboBox Colours
        setColour(juce::ComboBox::backgroundColourId, BlomeColour_3);
        setColour(juce::ComboBox::outlineColourId, BlomeColour_2);
        setColour(juce::ComboBox::arrowColourId, BlomeColour_1);
        setColour(juce::ComboBox::textColourId, BlomeColour_1);
        
        // Button Text Colours
        setColour(juce::TextButton::buttonColourId, BlomeColour_1);
        setColour(juce::TextButton::textColourOnId, BlomeColour_1);
        setColour(juce::TextButton::textColourOffId, BlomeColour_1);
    }
    
    virtual ~BlomeLookAndFeel() {
        
    }
    
    /** Buttons */
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override
    {
        return font_1;
    }
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        juce::Colour fillColour;
        
        if(shouldDrawButtonAsDown) {
            fillColour = BlomeColour_6;
        } else if(shouldDrawButtonAsHighlighted) {
            fillColour = BlomeColour_5;
        } else {
            fillColour = BlomeColour_3;
        }
        
        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }
    
    /** ComboBoxes */
    juce::Font getLabelFont(juce::Label& label) override
    {
        return font_1;
    }
    
    void drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                            bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                            const juce::String& text, const juce::String& shortcutKeyText,
                            const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        juce::Rectangle<int> r (area);
        
        juce::Colour fillColour = isHighlighted ? BlomeColour_5 : BlomeColour_4;
        g.setColour(fillColour);
        
        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);
        
        juce::Colour fontColour = isTicked ? BlomeColour_7 : BlomeColour_1;
        g.setColour(fontColour);
        g.setFont(font_1);
        
        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, juce::Justification::left, 1);
    }
    
    void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       juce::ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour(BlomeColour_3);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
        
        juce::Rectangle<int> arrow (width - 30, 0, 20, height);
        
        juce::Path path;
        
        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);
        
        juce::Colour arrowColour = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        
        g.setColour(arrowColour);
        g.strokePath(path, juce::PathStrokeType(2.0f));
    }
    
    /** Sliders **/
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
        
        const float radius = juce::jmin(width * 0.5, height * 0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage(mSliderImage,
                    rx,
                    ry,
                    2 * radius,
                    2 * radius,
                    0,
                    frameIndex * mSliderImage.getWidth(),
                    mSliderImage.getWidth(),
                    mSliderImage.getWidth());
    }
    
private:
    juce::Image mSliderImage;
};
