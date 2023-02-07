#pragma once

#include <JuceHeader.h>

class ScaleEstimator : public juce::Component
{
public:
    ScaleEstimator()
    {        
    }

    void paint (juce::Graphics& g) override 
    {
    }

    void resized() override
    {
    }

private:
    ImageComponent circleOfFifthsImage;
    const std::array<const String, 12> notes = { "C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B" };


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleEstimator)
};
