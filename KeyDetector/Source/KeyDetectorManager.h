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
#include <chrono>

using namespace juce;


#define BUFFER_SECONDS 10
#define UPDATE_INTERVAL 3 * 1000 // 3 seconds
#define key_qeueu_t std::priority_queue <std::pair<double, KeyFinder::key_t>>


class KeyDetectorManager : public Timer // makes the gui hang for a bit, try with Thread instead?
{
public:
    KeyDetectorManager(int sampleRate) : 
        inputBuffer(1, sampleRate * BUFFER_SECONDS) ,
        inputData(1, sampleRate * BUFFER_SECONDS)
        
    {
        sampleMin = sampleRate;
        sampleMax = sampleRate * BUFFER_SECONDS;
        keyFinderInput.setChannels(1);
        keyFinderInput.setFrameRate(sampleRate);
        
        inputBuffer.setSize(1, sampleRate * BUFFER_SECONDS);
        inputBuffer.clear();
        startTimer(UPDATE_INTERVAL);
    }

    void timerCallback() override {
        // overriden function controlled and inhereted from Timer
        calculate();
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

    void pushBlock(AudioSampleBuffer samples, int numSamples) {
        inputBuffer.addToFifo(samples, numSamples);
    }

    key_qeueu_t getKeys() {
        return sortedKeys;
    }

    void toggleRecord() {
        //untested
        recording = !recording;
    }

    void reset() {
        // untested
        inputBuffer.clear();
        inputBuffer.reset();
        inputData.clear();
        keyFinderInput.resetIterators();
    }

private:
    AudioBufferFIFO<float> inputBuffer;
    AudioSampleBuffer inputData;
    
    unsigned int sampleMin, sampleMax = 0;
    KeyFinder::AudioData keyFinderInput;
    
    KeyFinder::KeyFinder keyFinder;
    key_qeueu_t sortedKeys;
    
    bool recording = true;
    bool clear = false;

};