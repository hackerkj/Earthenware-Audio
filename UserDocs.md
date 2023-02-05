## Key Detector

## Background
The JUCE framework is used to create and build this software. The Key Detector software has dual function has an instrument tuner and as an identifier for a musical key. Existing solution for key identificaiton usually run on audio files and are not suitable for real-time use. This software fills that gap by providing key identification with the same real-time efficacy as an instrument tuner.

## Running Key Detector
Key Detector can either be ran from the already compiled vst3 plugin or built manually. The generated vst3 plugin must be placed in the search path for your audio workstaitons VST directory. Alternatively, a standalone executable can be generated in the build process.

### Building
Navigate to `JUCE/extras/Projucer/Builds`. Select the build option for your respective platform (Linux, OSX, Windows) and run Projucer. Projucer is the tool used for simple generation of the project build resources. In Projucer go to `File->Open` and naviate to `Key Detector`. Load `KeyDetector.jucer`. On the top bar, select your respect platform and export it. When built, a build directory will be generated in the same folder with the options for a VST plugin and a standalone executable.

## Understanding the Plugin
![image](https://user-images.githubusercontent.com/43866259/216837084-e59629e3-a0cc-495d-a741-ceea87e65fec.png)
#### Scale Estimator Display
In the top left is the display for indicating which group of scales is most likely being played at the moment. This is indicated by a spline with the more likely scale having a greater curve point in its direction. Clicking on a key will display on the piano roll on the bottom.
#### Note Display
In the top right is the display for the current note being played.
#### Audio Controls
Below the note display are the audio controls for starting and stopping the plugin from listening to a given audio input. The quantize button is for adjusting the rate in which audio is gathered for scale analysis. It is recommened to adjust this setting according to the average subdivision of what is currently being played as well as accommidating for the tempo. The reset button will erase the last selected key and note being displayed.
#### Keyboard
The keyboard will display the selected key and show what is in-key, out-of-key, the current note being played, and the root of the scale.
## External Links and Sources
[FFTW](http://www.fftw.org)

[JUCE Framework](https://juce.com/)

[libkeyfinder](https://github.com/mixxxdj/libkeyfinder)
