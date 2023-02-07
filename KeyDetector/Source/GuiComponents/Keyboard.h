#pragma once
#include <JuceHeader.h>
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


        setSize (600, 350);
    }

    void paint (juce::Graphics& g) override
    {
    }

    void resized() override
    {
        auto area = getLocalBounds();

        keyboardComponent.setBounds (area);
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

    double startTime;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};