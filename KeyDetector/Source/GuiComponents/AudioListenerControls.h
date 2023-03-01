#pragma once
#include <JuceHeader.h>
#include "KeyDetectorManager.h"

class AudioListenerControls   : public juce::Component, 
                                public juce::Button::Listener
{
public:
    AudioListenerControls()
    {
        
        audioPlayPauseBtn.onClick = [this] ()
        {
            if(isPlaying) pause(); else play();
        };
        audioPlayPauseBtn.addListener(this);
        audioPlayPauseBtn.setButtonText(playString);
        addAndMakeVisible(audioPlayPauseBtn);

        resetBtn.onClick = [this] ()
        {
            reset();
        };
        resetBtn.addListener(this);
        resetBtn.setButtonText(resetString);
        addAndMakeVisible(resetBtn);
        setSize(300, 300);
    }

    void paint (juce::Graphics& g) override 
    {
    }

    void resized() override
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();
        audioPlayPauseBtn.setBounds(localX, localY + 25, 180, 40);
        resetBtn.setBounds(localX, localY + 75, 180, 40);
    }
 
    void buttonClicked (juce::Button* button) override 
    {
    }
    
    bool getIsReset()
    {
        return isReset;
    }
    

private:
    void play() 
    {
        isPlaying = true;
        audioPlayPauseBtn.setButtonText(pauseString);
        keyDetectorManager->toggleRecord();
    }

    void pause()
    {
        isPlaying = false;
        audioPlayPauseBtn.setButtonText(playString);
        keyDetectorManager->toggleRecord();
    }

    void reset()
    {
        isReset = true;
        keyDetectorManager->reset();
    }

    ComboBox quantityMenu;

    juce::TextButton audioPlayPauseBtn;
    juce::TextButton resetBtn;
    juce::String playString = "Playing";
    juce::String pauseString = "Paused";
    juce::String resetString = "Reset";
    
    bool isPlaying = false;
    bool isReset = false;

    KeyDetectorManager* keyDetectorManager = KeyDetectorManager::getInstance(44100);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioListenerControls)
};