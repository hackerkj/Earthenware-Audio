#pragma once
#include <JuceHeader.h>

class ColorKey   :  public juce::Component
{
public:
    ColorKey()
    {
    
    }
    
    void paint (juce::Graphics& g) override 
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();
        float localHeight = 15.0;
        float localWidth = 15.0;

        g.setColour(Colours::teal);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setColour(Colours::black);
        g.drawText("Root", localX + 20.0, localY- 5.0,  30.0, 30.0, juce::Justification::centred, 30.f);
        localX += 80.0;

        g.setColour(Colours::blue);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setColour(Colours::black);
        g.drawText("Active", localX, localY - 5.0,  80.0, 30.0, juce::Justification::centred, 30.f);
        localX += 80.0;
     
        g.setColour(Colours::aqua);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setColour(Colours::black);
        g.drawText("Key", localX, localY- 5.0,  80.0, 30.0, juce::Justification::centred, 30.f);
        localX += 80.0;

        g.setColour(Colours::green);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setColour(Colours::black);
        g.drawText("In-Key", localX, localY- 5.0,  80.0, 30.0, juce::Justification::centred, 30.f);
        localX += 80.0;

        g.setColour(Colours::red);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setColour(Colours::black);
        g.drawText("Out-of-Key", localX + 10.0, localY- 5.0,  85.0, 30.0, juce::Justification::centred, 30.f);
    }

    void resized() override
    {
    }

private:


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColorKey)
};