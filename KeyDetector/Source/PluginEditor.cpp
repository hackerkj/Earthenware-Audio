/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


// utilities for frequency <-> note
// were assuming a standard 440hz A4
int noteFromPitch(float frequency) {
    float noteNum = 12.0 * (log(frequency / 440.0) / log(2.0));
    noteNum = round(noteNum) + 69;
    return noteNum;
}

float frequencyFromNoteNumber(int note) {
    return 440.0 * pow(2.0, (note - 69) / 12.0);
}

float centsOffFromPitch(float frequency, int note) {
    // if this returns over or under +/- 50 something is wrong
    float frqFromNote = frequencyFromNoteNumber(note);
    float logOfPitch = log(frequency / frqFromNote);
    return floor(1200.0 * logOfPitch) / log(2.0);
}

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
    //TODO::add cents counter, figure out the jumpiness in the slider animation,
    // maybe separate out the moving parts away from the static ones.
    float freq = audioProcessor.getPitch();
    unsigned int note = noteFromPitch(freq);
    float cents = centsOffFromPitch(freq, note);
    const std::array<const String, 12> notes = { "C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B" };

    tunerBox.setNote(notes[note % 12]);
    tunerBox.setCents(cents);
    tunerBox.repaint();
    scaleEstimator.repaint();
}
