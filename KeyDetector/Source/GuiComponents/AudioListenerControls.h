#pragma once
#include <JuceHeader.h>

class AudioListenerControls   : public juce::Component, 
                                public juce::Button::Listener
{
public:
    AudioListenerControls()
    {
        quantityMenu.addItem (1, "1/2");
        quantityMenu.addItem (2, "1/4");
        quantityMenu.addItem (3, "1/8");
        quantityMenu.addItem (4, "1/16");

        quantityMenu.showMenuAsync (PopupMenu::Options(),
            [] (int result)
            {
                switch (result)
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
            });

        audioPlayPauseBtn.onClick = [this] ()
        {
            if(isPlaying) pause(); else play();
        };
        audioPlayPauseBtn.addListener(this);

        addAndMakeVisible(audioPlayPauseBtn);

        resetBtn.onClick = [this] ()
        {
            reset();
        };
        audioPlayPauseBtn.addListener(this);

        addAndMakeVisible(audioPlayPauseBtn);

        setSize (600, 400);
    }

    void paint (juce::Graphics& g) override 
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();
        int currentPosition = 5;
        
    }

    void resized() override
    {
    }

private:
    void play() 
    {

    }

    void pause()
    {

    }

    void reset()
    {
        
    }

    PopupMenu quantityMenu;
    juce::ImageButton audioPlayPauseBtn;
    juce::ImageButton resetBtn;
    bool isPlaying = false;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioListenerControls)
};