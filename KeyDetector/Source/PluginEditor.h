/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TuneBoxrComponent.h"


//==============================================================================
/**
*/
class KeyDetectorAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    KeyDetectorAudioProcessorEditor (KeyDetectorAudioProcessor&);
    ~KeyDetectorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KeyDetectorAudioProcessor& audioProcessor;
    TunerBoxComponent tunerBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyDetectorAudioProcessorEditor)
};
