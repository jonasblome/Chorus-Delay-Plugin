/*
  ==============================================================================

    BlomeAudioHelper.h
    Created: 8 Feb 2023 11:30:12pm
    Author:  Jonas Blome

  ==============================================================================
*/

#pragma once

const static double kPI = 3.14159265359;
const static double k2PI = 6.28318530718;
const static int maxBufferSize = 192000;

inline float blome_linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}
