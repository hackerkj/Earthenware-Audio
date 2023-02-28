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
        setKey(KeyFinder::key_t::C_MAJOR);
        addAndMakeVisible (keyboardComponent);
        keyboardState.addListener (this);
        keyboardState.reset();

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
                keyboardComponent.setCurrentKey({6, 8, 0, 1, 3, 5, 7});
                break;
            case KeyFinder::key_t::A_FLAT_MINOR:
                keyboardComponent.setCurrentKey({1, 3, 4, 6, 8, 10, 11});
                break;
            case KeyFinder::key_t::A_MAJOR:
                keyboardComponent.setCurrentKey({1, 2, 4, 6, 8, 9, 11});
                break;
            case KeyFinder::key_t::A_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 5, 7, 9, 11});
                break;
            case KeyFinder::key_t::B_FLAT_MAJOR:
                keyboardComponent.setCurrentKey({0, 2, 3, 5, 7, 9, 10});
                break;
            case KeyFinder::key_t::B_FLAT_MINOR:
                keyboardComponent.setCurrentKey({0, 1, 3, 5, 7, 8, 10});
                break;
            case KeyFinder::key_t::B_MAJOR:
                keyboardComponent.setCurrentKey({1, 3, 4, 6, 8, 10, 11});
                break;
            case KeyFinder::key_t::B_MINOR:
                keyboardComponent.setCurrentKey({1, 2, 4, 6, 8, 9, 11});
                break;
            case KeyFinder::key_t::C_MAJOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 5, 7, 9, 11});
                break;
            case KeyFinder::key_t::C_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 3, 5, 7, 9});
                break;
            case KeyFinder::key_t::D_FLAT_MAJOR:
                keyboardComponent.setCurrentKey({0, 1, 3, 5, 6, 8});
                break;
            case KeyFinder::key_t::D_FLAT_MINOR:
                keyboardComponent.setCurrentKey({1, 3, 4, 6, 8, 10, 11});
                break;
            case KeyFinder::key_t::D_MAJOR:
                keyboardComponent.setCurrentKey({1, 2, 4, 6, 7, 9, 11});
                break;
            case KeyFinder::key_t::D_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 5, 7, 9, 11});
                break;
            case KeyFinder::key_t::E_FLAT_MAJOR:
                keyboardComponent.setCurrentKey({0, 2, 3, 5, 7, 8, 10});
                break;
            case KeyFinder::key_t::E_FLAT_MINOR:
                keyboardComponent.setCurrentKey({1, 3, 5, 6, 8, 10, 11});
                break;
            case KeyFinder::key_t::E_MAJOR:
                keyboardComponent.setCurrentKey({1, 3, 4, 6, 8, 9, 11});
                break;
            case KeyFinder::key_t::E_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 6, 7, 9, 11});
                break;
             case KeyFinder::key_t::F_MAJOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 5, 7, 9, 10});
                break;
            case KeyFinder::key_t::F_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 3, 5, 7, 8, 10});
                break;
            case KeyFinder::key_t::G_FLAT_MAJOR:
                keyboardComponent.setCurrentKey({1, 3, 5, 6, 8, 10, 11});
                break;
            case KeyFinder::key_t::G_FLAT_MINOR:
                keyboardComponent.setCurrentKey({1, 3, 4, 6, 8, 9, 11});
                break;
            case KeyFinder::key_t::G_MAJOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 6, 7, 9, 11});
                break;
            case KeyFinder::key_t::G_MINOR:
                keyboardComponent.setCurrentKey({0, 2, 4, 5, 7, 9, 10});
                break;
            case KeyFinder::key_t::SILENCE:
                keyboardComponent.setCurrentKey({});
                break;
        }
        keyboardComponent.timerCallback();
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
    std::vector<int> midiNumberList;
    KeyFinder::key_t currentKey = KeyFinder::key_t::C_MAJOR;

    double startTime;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};