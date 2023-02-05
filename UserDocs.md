## Key Detector

## Background

## Running Key Detector
Key Detector can either be ran from the already compiled vst3 plugin or built manually.

### Building
To build `Key Detector` run CMake on `CMakeLists.txt` within the `Key Detector` directory.

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
