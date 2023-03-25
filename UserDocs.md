## Key Detector

## Background
The JUCE framework is used to create and build this software. The Key Detector software has dual function has an instrument tuner and as an identifier for a musical key. Existing solution for key identificaiton usually run on audio files and are not suitable for real-time use. This software fills that gap by providing key identification with the same real-time efficacy as an instrument tuner.

### Building and Running
Navigate to `JUCE/extras/Projucer/Builds`. Select the build option for your respective platform (Linux, OSX, Windows) and run Projucer. Projucer is the tool used for simple generation of the project build resources. In Projucer go to `File->Open` and naviate to `Key Detector`. Load `KeyDetector.jucer`. On the top bar, select your respect platform and export it. When built, a build directory will be generated in the same folder with the options for a VST plugin and a standalone executable. The program will not build the first time, copy the fftw library named `libfftw3-3.dll` from `KeyDetector/Source/libKeyFinder/` into the newly generated build directory and build again. The VST3 and standalone executable build by default, however, only the standalone version is functional due to linking issues with the fftw library.

## Understanding the Plugin
![image](https://github.com/hackerkj/Earthenware-Audio/blob/main/KeyDetectorScreenshot.png)
#### Scale Estimator Display
In the top left is the display for indicating which group of scales is most likely being played at the moment. This is indicated by a horizontal bar graph corresponding to the proximity to a scale. Clicking on a bar will display the associated notes on the piano roll below.
#### Note Display
In the top right is the display for the current note being played. The note is also highlighted below on the piano roll when a key is slected to tell the user.
#### Audio Controls
The reset button will erase the last selected key and note being displayed. The play and pause button will stop the calculation of keys until it is pressed again.
#### Keyboard
The keyboard will display the selected key and show what is in-key, out-of-key, the current note being played, and the root of the scale.
## External Links and Sources
[FFTW](http://www.fftw.org)

[JUCE Framework](https://juce.com/)

[libkeyfinder](https://github.com/mixxxdj/libkeyfinder)
