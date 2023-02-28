/*
  ==============================================================================

    KeyDetector.h
    Created: 2 Feb 2023 12:54:12pm
    Author:  jpdub

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "keyfinder.h"
#include "AudioBufferFIFO.h"
#include "PitchYIN.h"
#include <chrono>

using namespace juce;


#define BUFFER_SECONDS 10
#define UPDATE_INTERVAL 3 * 1000 // 3 seconds
#define key_qeueu_t std::priority_queue <std::pair<double, KeyFinder::key_t>>




class KeyDetectorManager : public juce::Thread // makes the gui hang for a bit, try with Thread instead?
{

public:
    inline static KeyDetectorManager* instancePtr = NULL;
    // singletone design pattern for more direct access
    static KeyDetectorManager* getInstance(int sampleRate) {
        if (!instancePtr)
            instancePtr = new KeyDetectorManager(sampleRate);
        return instancePtr;
    }


    void calculate() {
        // pulls from a FIFO qeueu filled in our getNextBlock call
        // copies the data into the key detectors buffer for periodic analysis
        int ready = inputBuffer.getNumReady();

        // don't run if we have no data
        if (ready > 0 && recording) {
            inputBuffer.readFromFifo(inputData, ready);
            keyFinderInput.addToSampleCount(ready);

            // keyfinder has it's own buffer type to copy into
            for (int sample = 0; sample < ready; ++sample) {
                keyFinderInput.setSample(sample, inputData.getSample(0, sample));
            }

            // grab the keys in order of similarity with a priority qeueu
            if (keyFinderInput.getSampleCount() > sampleMin) {
                sortedKeys = keyFinder.sortedKeyOfAudio(keyFinderInput);
                sortedUpdated = true;
                clear = false;

            }

            // clear out the oldest data
            if (keyFinderInput.getFrameCount() > sampleMax) {
                keyFinderInput.discardFramesFromFront(ready);
                // haven't encountered this yet, good to check anyways
                if (keyFinderInput.getFrameCount() > sampleMax * 2) {
                    DBG("KeyDetectorManager.h is leaking memory");
                }
            }
        }
    }

    bool dataChanged() {
        if (sortedUpdated) {
            sortedUpdated = !sortedUpdated;
            return true;
        }
        else {
            return false;
        }
    }

    bool dataClear() {
        return clear;
    }

    void run() {
        while (!threadShouldExit()) {
            calculate();
            wait(UPDATE_INTERVAL);
        }

    }

    void pushBlock(AudioSampleBuffer samples, int numSamples) {
        if (recording) {
            inputBuffer.addToFifo(samples, numSamples);
        }
        yinBuffer.addToFifo(samples, numSamples);
        if (yinBuffer.getNumReady() >= 2048) {
            pitch = pitchYIN.getPitchInHz(yinData.getReadPointer(0));
            yinBuffer.readFromFifo(yinData, 2048);
            yinBuffer.clear();
        }
    }

    key_qeueu_t getKeys() {
        return sortedKeys;
    }

    void toggleRecord() {
        recording = !recording;
    }

    void reset() {
        // untested
        inputBuffer.clear();
        inputBuffer.reset();
        inputData.clear();
        keyFinderInput.resetIterators();
        keyFinderInput.discardFramesFromFront(keyFinderInput.getSampleCount());
        while (!sortedKeys.empty()) { sortedKeys.pop(); }
        clear = true;
    }

    float getPitch() {
        return pitch;
    }

    float getCeents() {
        return centsOffFromPitch(pitch, noteFromPitch(pitch));
    }

    String getNote() {
        // A1, C0, B#5 etc...
        unsigned int note = noteFromPitch(pitch);
        int octave = note / 12;
        const std::array<String, 12> notes = { "C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B" };

        return notes[note % 12] + String(octave);
    }


private:
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

    KeyDetectorManager(int sampleRate) :
        inputBuffer(1, sampleRate* BUFFER_SECONDS),
        inputData(1, sampleRate* BUFFER_SECONDS),
        Thread("keyManagerThread"), 
        pitchYIN(44100, 2048),
        yinBuffer(2, 4096),
        yinData(2, 2048)

    {
        sampleMin = sampleRate;
        sampleMax = sampleRate * BUFFER_SECONDS;
        keyFinderInput.setChannels(1);
        keyFinderInput.setFrameRate(sampleRate);

        inputBuffer.setSize(1, sampleRate * BUFFER_SECONDS);
        inputBuffer.clear();
        startThread();

        //pitchYIN.setSampleRate(static_cast<unsigned int> (sampleRate));
        //pitchYIN.setBufferSize(2048);
        yinData.clear();
        yinBuffer.clear();

    }
    // key detect
    AudioBufferFIFO<float> inputBuffer;
    AudioSampleBuffer inputData;
    unsigned int sampleMin, sampleMax = 0;
    KeyFinder::AudioData keyFinderInput;
    KeyFinder::KeyFinder keyFinder;
    key_qeueu_t sortedKeys;
    
    // buttons
    bool recording = true;
    bool clear = true;
    bool sortedUpdated = false;

    // tuner
    AudioBufferFIFO<float> yinBuffer;
    AudioSampleBuffer yinData;
    float pitch;
    PitchYIN pitchYIN;

};
