/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KeyDetectorAudioProcessor::KeyDetectorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), pitchYIN(44100, 2048)
    , yinBuffer(2, 4096)
    , yinData(2, 2048)

#endif
{
}

KeyDetectorAudioProcessor::~KeyDetectorAudioProcessor()
{
}

//==============================================================================
const juce::String KeyDetectorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KeyDetectorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KeyDetectorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KeyDetectorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif                                                         
}

double KeyDetectorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KeyDetectorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KeyDetectorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KeyDetectorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KeyDetectorAudioProcessor::getProgramName (int index)
{
    return {};
}

void KeyDetectorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KeyDetectorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    pitchYIN.setSampleRate(static_cast<unsigned int> (sampleRate));
    pitchYIN.setBufferSize(2048);
    yinData.clear();
    yinBuffer.clear();
}

void KeyDetectorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KeyDetectorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KeyDetectorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    auto* channelData = buffer.getReadPointer(0);

    // only grabs the first channel, mono signal
    // TODO
    // Make some sort of noise gate function so this only runs
    // when we're reasonably sure something is played, and a '-'
    // is displayed when that threshold isnt met.
    // Maybe just set a negative frequency and handle accordingly
    // The noise floor on my maachine seems to be around 10 ^-5
    yinBuffer.addToFifo(buffer, buffer.getNumSamples());
    if (yinBuffer.getNumReady() >= 2048) {
        pitch = pitchYIN.getPitchInHz(yinData.getReadPointer(0));
        yinBuffer.readFromFifo(yinData, 2048);
        yinBuffer.clear();
    }
    
    keyDetectorManager->pushBlock(buffer, buffer.getNumSamples());

     //..do something to the data...
}

//==============================================================================
bool KeyDetectorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KeyDetectorAudioProcessor::createEditor()
{
    return new KeyDetectorAudioProcessorEditor (*this);
}

//==============================================================================
void KeyDetectorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KeyDetectorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

float KeyDetectorAudioProcessor::getPitch()
{
    return pitch;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KeyDetectorAudioProcessor();
}
