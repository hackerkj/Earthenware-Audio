#pragma once

#include <JuceHeader.h>
#include "keyfinder.h"

class ScaleEstimator : public juce::Component, 
                       public juce::Button::Listener
{
public:
    ScaleEstimator()
    {
        firstScale.onClick = [this] ()
        {
            setScale(rankings[0]);
        };
        firstScale.addListener(this);
        addAndMakeVisible(firstScale);
        firstScale.setColour(TextButton::buttonColourId, juce::Colours::red);

        secondScale.onClick = [this] ()
        {
            setScale(rankings[1]);

        };
        secondScale.addListener(this);
        addAndMakeVisible(secondScale);
        secondScale.setColour(TextButton::buttonColourId, juce::Colours::lightseagreen);

        thirdScale.onClick = [this] ()
        {   
            setScale(rankings[2]);
        };
        thirdScale.addListener(this);
        addAndMakeVisible(thirdScale);
        thirdScale.setColour(TextButton::buttonColourId, juce::Colours::lightblue);

        fourthScale.onClick = [this] ()
        {
            setScale(rankings[3]);
        };
        fourthScale.addListener(this);
        addAndMakeVisible(fourthScale);
        fourthScale.setColour(TextButton::buttonColourId, juce::Colours::lightpink);
    }

    void paint (juce::Graphics& g) override 
    {        
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY() + 5.0;
        float localHeight = 260.0;
        float localWidth = 320.0;

        g.setColour(Colours::white);
        g.drawRect(localX, localY, localWidth, localHeight);
        
    }

    void resized() override
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();

        localX += 5.0; localY += 5.0;
        firstScale.setBounds(localX, localY + 10.0, 300, 50);
        localY += 65.0;
        secondScale.setBounds(localX, localY, 240, 50);
        localY += 55.0;
        thirdScale.setBounds(localX, localY, 170, 50);
        localY += 55.0;
        fourthScale.setBounds(localX, localY, 90, 50);
    }

    void buttonClicked (juce::Button* button) override 
    {
    }

    void getKeyRankings()
    {
       auto keys = kdManager->getKeys();
        rankings[0] = keys.top().second;
      //  firstScale.setButtonText();

        keys.pop();
        rankings[1] = keys.top().second;
     //  secondScale.setButtonText();

        keys.pop();
        rankings[2] = keys.top().second;
    //  thirdScale.setButtonText();

        keys.pop();
        rankings[3] = keys.top().second;
    //  fourthScale.setButtonText(); 
    }

    key_t getKeyToDisplay()
    {
        return currentKey;
    }
    
private:
    juce::TextButton firstScale;
    juce::TextButton secondScale;
    juce::TextButton thirdScale;
    juce::TextButton fourthScale;

    std::map<int, KeyFinder::key_t> rankings;
    KeyFinder::key_t currentKey;
    
    KeyDetectorManager* kdManager = new KeyDetectorManager(1000);

    void setScale(KeyFinder::key_t key)
    {
        currentKey = key;
    }


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleEstimator)
};
