#pragma once
#include <JuceHeader.h>
#include "keyfinder.h"

//==============================================================================
class Keyboard  : public juce::Component,
                              private juce::MidiInputCallback,
                              private juce::MidiKeyboardStateListener
{
public:
    Keyboard()
    : keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
        startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
    {
        setOpaque (true);

        addAndMakeVisible (keyboardComponent);
        keyboardState.addListener (this);

        setSize (800, 350);
    }

    void paint (juce::Graphics& g) override
    {
    }

    void resized() override
    {
        auto area = getLocalBounds();

        keyboardComponent.setBounds (area);
    }

    void setKey(KeyFinder::key_t key)
    {
        if(currentKey == key)
        {
            return;
        }

        currentKey = key;

        switch(currentKey)
        {
            case KeyFinder::key_t::A_FLAT_MAJOR:
                break;
            case KeyFinder::key_t::A_FLAT_MINOR:
                break;
            case KeyFinder::key_t::A_MAJOR:
                break;
            case KeyFinder::key_t::A_MINOR:
                break;
            case KeyFinder::key_t::B_FLAT_MAJOR:
                break;
            case KeyFinder::key_t::B_FLAT_MINOR:
                break;
            case KeyFinder::key_t::B_MAJOR:
                break;
            case KeyFinder::key_t::B_MINOR:
                break;
            case KeyFinder::key_t::C_MAJOR:
                break;
            case KeyFinder::key_t::C_MINOR:
                break;
            case KeyFinder::key_t::D_FLAT_MAJOR:
                break;
            case KeyFinder::key_t::D_FLAT_MINOR:
                break;
            case KeyFinder::key_t::D_MAJOR:
                break;
            case KeyFinder::key_t::D_MINOR:
                break;
            case KeyFinder::key_t::E_FLAT_MAJOR:
                break;
            case KeyFinder::key_t::E_FLAT_MINOR:
                break;
            case KeyFinder::key_t::E_MAJOR:
                break;
            case KeyFinder::key_t::E_MINOR:
                break;
             case KeyFinder::key_t::F_MAJOR:
                break;
            case KeyFinder::key_t::F_MINOR:
                break;
            case KeyFinder::key_t::G_FLAT_MAJOR:
                break;
            case KeyFinder::key_t::G_FLAT_MINOR:
                break;
            case KeyFinder::key_t::G_MAJOR:
                break;
            case KeyFinder::key_t::G_MINOR:
                break;
            case KeyFinder::key_t::SILENCE:
                break;


        }
        repaint();
    }

private:
    void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message) override
    {
    }

    void handleNoteOn (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
    {
    }

    void handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override
    {
    }

    juce::MidiKeyboardState keyboardState;            
    juce::MidiKeyboardComponent keyboardComponent;    
    KeyFinder::key_t currentKey;

    double startTime;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};