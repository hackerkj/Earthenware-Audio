#pragma once
#include <JuceHeader.h>
#include "keyfinder.h"
#include "ColorMidiKeyboardComponent.h"

//==============================================================================
class Keyboard  : public juce::Component,
                              private juce::MidiInputCallback,
                              private juce::MidiKeyboardStateListener
{
public:
    Keyboard()
    : keyboardComponent (keyboardState, ColorMidiKeyboardComponent::horizontalKeyboard),
        startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
    {
        setOpaque (true);
        setKey();
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

    void setKey()
    {
        int root = (abs((int)kdManager->getSelectedKey() - 6) / 2 ) % 12;
        keyboardComponent.setScaleNotes(kdManager->getScaleNotes(), root);
        keyboardComponent.setPlayedNote(kdManager->getMIDINote());
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
    juce::ColorMidiKeyboardComponent keyboardComponent;
    std::vector<int> midiNumberList;
    KeyDetectorManager* kdManager = KeyDetectorManager::getInstance(44100);

    double startTime;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};