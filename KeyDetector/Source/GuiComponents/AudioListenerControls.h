#pragma once
#include <JuceHeader.h>

class AudioListenerControls   : public juce::Component, 
                                public juce::Button::Listener
{
public:
    AudioListenerControls()
    {
        quantityMenu.addItem ("1/2", 0);
        quantityMenu.addItem ("1/4", 1);
        quantityMenu.addItem ("1/8", 2);
        quantityMenu.addItem ("1/16", 3);
        quantityMenu.addItem ("1/32", 4);
        quantityMenu.onChange = [this] { 
            switch (quantityMenu.getSelectedId())
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
            }
        };

        addAndMakeVisible (quantityMenu);
        quantityMenu.setSelectedId (1);
        
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
        quantityMenu.setBounds(localX, localY, 85, 30);
        audioPlayPauseBtn.setBounds(localX, localY + 45, 85, 30);
        resetBtn.setBounds(localX + 90.0, localY+ 45, 85, 30);
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
    }

    void pause()
    {
        isPlaying = false;
        audioPlayPauseBtn.setButtonText(playString);
    }

    void reset()
    {
        isReset = true;
    }

    ComboBox quantityMenu;

    juce::TextButton audioPlayPauseBtn;
    juce::TextButton resetBtn;
    juce::String playString = "play";
    juce::String pauseString = "pause";
    juce::String resetString = "reset";
    
    bool isPlaying = false;
    bool isReset = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioListenerControls)
};