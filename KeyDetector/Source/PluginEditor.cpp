/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"




//==============================================================================
KeyDetectorAudioProcessorEditor::KeyDetectorAudioProcessorEditor (KeyDetectorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    
    addAndMakeVisible(tunerBox);
    addAndMakeVisible(keyboard);
    addAndMakeVisible(audioListenerControls);
    addAndMakeVisible(scaleEstimator);
    addAndMakeVisible(colorKey);

    startTimerHz(30);
}

KeyDetectorAudioProcessorEditor::~KeyDetectorAudioProcessorEditor()
{
}

//==============================================================================
void KeyDetectorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
}

void KeyDetectorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int margin = 10;
    int height = 400;
    int width = 600;
    int centerDiv = width * 0.65;

    tunerBox.setBounds(centerDiv, margin, width - centerDiv - 2 * margin, 140);
    tunerBox.resize();
    scaleEstimator.setBounds(margin, margin, centerDiv - margin * 2, height * 0.65 + margin);
    audioListenerControls.setBounds(centerDiv,  height * 0.4, 300, 300);
    colorKey.setBounds(margin, height - (height * 0.25), 450, 350);
    keyboard.setBounds(margin, height - (height * 0.15), width- 2 * margin, height * 0.15);
}

void KeyDetectorAudioProcessorEditor::timerCallback()
{
    tunerBox.repaint();
    scaleEstimator.repaint();
    keyboard.setKey();
}
