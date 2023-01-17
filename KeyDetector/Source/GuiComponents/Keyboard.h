/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             HandlingMidiEventsTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Handles incoming midi events.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once
#include <JuceHeader.h>
//==============================================================================
class Keyboard  : public juce::Component,
                              private juce::MidiInputCallback,
                              private juce::MidiKeyboardStateListener
{
public:
//! [initialiser]
    Keyboard()
      : keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
        startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
    {
        addAndMakeVisible (keyboardComponent);
        keyboardState.addListener (this);
        setSize (600, 400);
    }

    ~Keyboard() override
    {
        keyboardState.removeListener (this);
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        for(auto idx : currentScale)
        {
            keyboardComponent.drawWhiteNote(1,)
        }

    }

    void updateScale(std::vector<int> notes) 
    {
        currentScale = notes;
        keyboardComponent.repaint();
    }

    void removeScale()
    {
        currentScale.clear();
        
    }

    void resized() override
    {
        auto area = getLocalBounds();
        keyboardComponent.setBounds (area.removeFromTop (80).reduced(8));
    }

private:
    juce::MidiKeyboardState keyboardState;           
    juce::MidiKeyboardComponent keyboardComponent;    
    juce::TextEditor midiMessagesBox;
    
    std::vector<int> currentScale;

    double startTime;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};