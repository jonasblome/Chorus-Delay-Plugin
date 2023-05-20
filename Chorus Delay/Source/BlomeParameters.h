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
    kParameter_FilterCutoff,
    kParameter_FilterActivated,
    kParameter_FilterType,
    kParameter_TotalNumParameters,
};

static juce::NormalisableRange<float> BlomeParameterRanges [kParameter_TotalNumParameters] =
{
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 1.0f),
    juce::NormalisableRange<float>(0.0f, 2.0f),
};

static float BlomeParameterDefaultValues [kParameter_TotalNumParameters] =
{
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.0f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    1.0f,
    2.0f,
};

static juce::String BlomeParameterID [kParameter_TotalNumParameters] =
{
    "InputGain",
    "Time",
    "Feedback",
    "WetDry",
    "FXType",
    "OutputGain",
    "ModulationRate",
    "ModulationDepth",
    "FilterCutoff",
    "FilterActivated",
    "FilterType",
};

static juce::String BlomeParameterLabels [kParameter_TotalNumParameters] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "Wet/Dry",
    "Type",
    "Output Gain",
    "Rate",
    "Depth",
    "Filter Cutoff",
    "Filter Type",
};
