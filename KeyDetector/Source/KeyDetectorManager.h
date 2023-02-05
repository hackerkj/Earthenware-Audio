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


#define BUFFER_SECONDS 6

class KeyDetectorManager : public Thread
{
public:
    KeyDetectorManager(int sampleRate) : 
        inputBuffer(1, sampleRate * BUFFER_SECONDS) ,
        inputData(1, sampleRate * BUFFER_SECONDS),
        Thread("KeyDetectThread")
        
    {
        sampleMin = sampleRate;
        sampleMax = sampleRate * BUFFER_SECONDS;
        keyFinderInput.setChannels(1);
        keyFinderInput.setFrameRate(sampleRate);
        
        inputBuffer.setSize(1, sampleRate * BUFFER_SECONDS);
        inputBuffer.clear();
        startThread();
    }
    ~KeyDetectorManager() {
        stopThread(1000);
    }

    void stopTimer() {

    }

    void run() override {
        while (!threadShouldExit()) {
            wait(1000);
            calculate();
        }
    }

    void calculate() {
        int ready = inputBuffer.getNumReady();

        if (ready > 0) {
            inputBuffer.readFromFifo(inputData, ready);
            keyFinderInput.addToSampleCount(ready);

            for (int sample = 0; sample < ready; ++sample) {
                keyFinderInput.setSample(sample, inputData.getSample(0, sample));
                //DBG(inputData.getSample(0, sample));
            }

            if (keyFinderInput.getFrameCount() > sampleMax) {
                keyFinderInput.discardFramesFromFront(ready);
                if (keyFinderInput.getFrameCount() > sampleMax * 2) {
                    DBG("KeyDetectorManager.h is leaking memory");
                }
            }

            if (keyFinderInput.getSampleCount() > sampleMin) {
                auto start = std::chrono::high_resolution_clock::now();
                key = keyFinder.keyOfAudio(keyFinderInput);
                if (key == 24) DBG("silence detected");
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                //DBG(duration.count());
            }
            DBG(key);
        }
    }

    void pushBlock(AudioSampleBuffer samples, int numSamples) {
        inputBuffer.addToFifo(samples, numSamples);
    }

    KeyFinder::key_t getKey() {
        return key;
    }

private:
    AudioBufferFIFO<float> inputBuffer;
    AudioSampleBuffer inputData;
    
    unsigned int sampleMin, sampleMax = 0;
    KeyFinder::AudioData keyFinderInput;
    

    KeyFinder::KeyFinder keyFinder;
    KeyFinder::key_t key; // eventually make this an ordered qeue

};