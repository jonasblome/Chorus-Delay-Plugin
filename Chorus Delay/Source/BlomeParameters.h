/*
  ==============================================================================

    BlomeParameteres.h
    Created: 12 Feb 2023 7:14:58pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

enum BlomeParameter
{
    kParameter_InputGain = 0,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_DelayWetDry,
    kParameter_DelayType, // Chorus or delay?
    kParameter_OutputGain,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_TotalNumParameters
};

static juce::String BlomeParameterID [kParameter_TotalNumParameters] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "Wet Dry",
    "Type",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth",
};
