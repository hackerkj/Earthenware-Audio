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
            setScale(rankings[0].second);
        };
        firstScale.addListener(this);
        addAndMakeVisible(firstScale);
        firstScale.setColour(TextButton::buttonColourId, juce::Colours::green);

        secondScale.onClick = [this] ()
        {
            setScale(rankings[1].second);

        };
        secondScale.addListener(this);
        addAndMakeVisible(secondScale);
        secondScale.setColour(TextButton::buttonColourId, juce::Colours::green);

        thirdScale.onClick = [this] ()
        {   
            setScale(rankings[2].second);
        };
        thirdScale.addListener(this);
        addAndMakeVisible(thirdScale);
        thirdScale.setColour(TextButton::buttonColourId, juce::Colours::green);

        fourthScale.onClick = [this] ()
        {
            setScale(rankings[3].second);
        };
        fourthScale.addListener(this);
        addAndMakeVisible(fourthScale);
        fourthScale.setColour(TextButton::buttonColourId, juce::Colours::green);
    }

    void paint (juce::Graphics& g) override 
    {        
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();
        float localHeight = getLocalBounds().getHeight();
        float localWidth = getLocalBounds().getWidth();

        g.setColour(Colours::black);
        g.fillRect(localX, localY, localWidth, localHeight);
        g.setFillType(Colours::darkblue);
        g.drawRect(localX, localY, localWidth, localHeight);



        if (kdManager->dataChanged() || kdManager->dataClear()) {
            getKeyRankings();
            if (kdManager->dataClear()) {
                rankings[0].first = rankings[1].first = rankings[2].first = rankings[3].first = 0.0;
            }

            localY += 10.0;
            firstScale.setBounds(localX, localY, localWidth * rankings[0].first, 50);
            localY += 55.0;
            secondScale.setBounds(localX, localY, localWidth * rankings[1].first -10, 50);
            localY += 55.0;
            thirdScale.setBounds(localX, localY, localWidth * rankings[2].first -20, 50);
            localY += 55.0;
            fourthScale.setBounds(localX, localY, localWidth * rankings[3].first -30, 50);
        }
    }

    void resized() override
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();


    }

    void buttonClicked (juce::Button* button) override 
    {
    }

    void getKeyRankings()
    {
        auto keys = kdManager->getKeys();
        if (!keys.empty()) {
            rankings[0] = keys.top();
            firstScale.setButtonText(KeyFinder::keyStrings[(int)rankings[0].second]);
            keys.pop();
            rankings[1] = keys.top();
            secondScale.setButtonText(KeyFinder::keyStrings[(int)rankings[1].second]);
            keys.pop();
            rankings[2] = keys.top();
            thirdScale.setButtonText(KeyFinder::keyStrings[(int)rankings[2].second]);
            keys.pop();
            rankings[3] = keys.top();
            fourthScale.setButtonText(KeyFinder::keyStrings[(int)rankings[3].second]);
        }
    }

    
private:
    juce::TextButton firstScale;
    juce::TextButton secondScale;
    juce::TextButton thirdScale;
    juce::TextButton fourthScale;

    bool firstToggle, secondToggle, thirdToggle, fouthToggle;

    std::pair<double, KeyFinder::key_t> rankings[4];
    KeyDetectorManager* kdManager = KeyDetectorManager::getInstance(44100);

    void setScale(KeyFinder::key_t key)
    {
        kdManager->setSelectedKey(key);
    }


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleEstimator)
};
