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
        // ComboBox Colours
        setColour(juce::ComboBox::backgroundColourId, BlomeColour_BlackLightTransparent);
        setColour(juce::ComboBox::outlineColourId, BlomeColour_Black);
        setColour(juce::ComboBox::arrowColourId, BlomeColour_LightGray);
        setColour(juce::ComboBox::textColourId, BlomeColour_LightGray);
        setColour(juce::PopupMenu::backgroundColourId, BlomeColour_DarkOrangeStrongTransparent);
        
        // Button Text Colours
        setColour(juce::TextButton::buttonColourId, BlomeColour_LightGray);
        setColour(juce::TextButton::textColourOnId, BlomeColour_LightGray);
        setColour(juce::TextButton::textColourOffId, BlomeColour_LightGray);
    }
    
    virtual ~BlomeLookAndFeel() {
        
    }
    
    /** Buttons */
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override
    {
        return font_small_bold;
    }
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button,
                               const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted,
                               bool shouldDrawButtonAsDown) override
    {
        juce::Colour fillColour;
        
        if(shouldDrawButtonAsDown) {
            fillColour = BlomeColour_BlackStrongTransparent;
        } else if(shouldDrawButtonAsHighlighted) {
            fillColour = BlomeColour_BlackLightTransparent;
        } else {
            fillColour = BlomeColour_BlackMediumTransparent;
        }
        
        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }
    
    void drawToggleButton (juce::Graphics& g,
                           juce::ToggleButton& button,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override
     {
         juce::Colour fillColour;
         float cornerSize = 6.0f;
         const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
         
         if(shouldDrawButtonAsHighlighted)
         {
             fillColour = BlomeColour_BlackLightTransparent;
         }
         else
         {
             fillColour = BlomeColour_BlackMediumTransparent;
         }

         if (!button.isEnabled())
         {
             g.setOpacity (0.5f);
         }
         
         g.setColour(fillColour);
         g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
         
         if(button.getToggleState())
         {
             cornerSize = 4.0f;
             g.setColour(BlomeColour_DarkOrange);
             g.fillRoundedRectangle(bounds.reduced(3), cornerSize);
         }
     }
    
    /** ComboBoxes */
    juce::Font getLabelFont(juce::Label& label) override
    {
        return font_small_bold;
    }
    
    void drawPopupMenuBackgroundWithOptions(juce::Graphics& g,
                                            int width,
                                            int height,
                                            const juce::PopupMenu::Options& options) override
    {
        g.setColour(findColour(juce::PopupMenu::backgroundColourId));
        g.fillRoundedRectangle(0, 2, width, height - 2, 3.0f);
    }
    
    void drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                            bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                            const juce::String& text, const juce::String& shortcutKeyText,
                            const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        juce::Rectangle<int> r (area);
        
        juce::Colour fontColour = isTicked ? BlomeColour_BlackStrongTransparent : BlomeColour_BlackLightTransparent;
        g.setColour(fontColour);
        g.setFont(isTicked ? font_small_accentuated : font_small_bold);
        
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
        
        g.setColour(BlomeColour_BlackMediumTransparent);
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
    
    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds(6, 1, box.getWidth() - 30, box.getHeight() - 2);
        label.setFont (getComboBoxFont(box));
    }
    
    /** Sliders **/
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override
    {
        g.setColour(BlomeColour_BlackMediumTransparent);
        g.fillEllipse(x + 6, y + 6, width - 14, height - 14);
        g.setColour(BlomeColour_LightGray);
        juce::Line<float> sliderTick = juce::Line<float>::fromStartAndAngle(juce::Point<float>(width * 0.5 - 1, height * 0.5 - 1), (width - 19) * 0.5, sliderPosProportional * M_PI * 1.5 - (M_PI * 0.75));
        g.drawLine(sliderTick, 2.0);
    }
    
private:
    
};
