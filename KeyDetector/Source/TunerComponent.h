 /*
  ==============================================================================

    TunerComponent.h
    Created: 15 Dec 2022 7:50:04pm
    Author:  jpdub

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

class HorizontalTunerBarComponent : public Component
{
public:
    HorizontalTunerBarComponent()
    {

    }
    void paint(Graphics& g) override
    {
        float localX = getLocalBounds().getX();
        float localY = getLocalBounds().getY();
        float localHeight = getLocalBounds().getHeight();
        float localWidth = getLocalBounds().getWidth();

        g.setColour(Colours::lightgrey);
        g.fillRect(localX, localY, 4.0, localHeight);
        g.fillRect(localX + localWidth-4, localY, 4.0, localHeight);
        g.fillRect(localX, localX + localHeight / 2, localWidth, 2.0);
        

        g.drawRect(localWidth / 2 - 5, localY, ((localX + localWidth) / 100.0) * 10.0, localY + localHeight, 2.0);
        if (abs(centsSmoothed) < 50.0) {
            float inner = 5.0;
            float outer = 20.0;
            // red's hsv is 0
            float hsvGreen = 1.0 / 3.0;
            float abs_cents = (abs(centsSmoothed));

            if (abs_cents < inner) {
                g.setColour(Colour::fromRGB(0, 255, 0));
                DBG(std::to_string(Colour::fromRGB(255, 0, 0).getHue()));
            }
            else if (abs_cents > outer) {
                g.setColour(Colour::fromRGB(255, 0, 0));
            }
            else {
                // approaches green as it gets close to the inner cents bound, red when closer to outer, yellow in the center.
                float hueRedToGreen =  hsvGreen - ((abs_cents - inner) / (outer - inner)) * hsvGreen; // 0-0.3333...

                //DBG(std::to_string(green) + "\t" std::to_string(red));
                //DBG(std::to_string(hueRedToGreen));
                g.setColour(Colour::fromHSV(hueRedToGreen, 1.0, 1.0, 1.0));
            }

            
            g.fillRect(localWidth / 2.0 - 5 + centsSmoothed * 2.0, localY, 
                        ((localX + localWidth) / 100.0) * 5.0, localY + localHeight);
        }

    }
    void resized() override
    {
    }
    void setCents(float cents)
    {
        // set cents as a smoothed rolling average
        // handle some edge cases
        if (cents > 50.0) {
            cents = 50.0;
        }
        if (cents < -50.0) {
            cents = -50.0;
        }
        this->cents = (cents + circBufferSize * centsSmoothed) / (circBufferSize+1);
        // circular buffer logic
        //this part stops the running total from going crazy
        if (avgIndex == 0) {
            centsSum = cents * circBufferSize;
        }
        avgIndex = (avgIndex + 1) % circBufferSize;
        
        centsRollingAverage[avgIndex] = cents;

        centsSum += cents;
        centsSum -= centsRollingAverage[(avgIndex + 1) % circBufferSize];
        centsSmoothed = centsSum /circBufferSize;
        
    }
private:
    float cents;

    float centsSmoothed = 0.0;
    // using this for smoothing. Functioning as a circular buffer/queue
    int avgIndex = 0;
    float centsSum = 0.0;
    // average of 20 samples, raise to smooth, lower to make more responsive
    static const unsigned int circBufferSize = 20; 
    float centsRollingAverage[circBufferSize];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HorizontalTunerBarComponent)
};

class TunerBoxComponent : public Component
{
public:
    TunerBoxComponent() {
        addAndMakeVisible(horizontalTunerBar);

    }

    void paint(Graphics& g) override
    {
        g.setColour(juce::Colours::black);
        g.fillAll();
        g.setColour(juce::Colours::darkslateblue);
        g.drawRect(juce::Rectangle(getWidth(), getHeight()));
        g.setColour(juce::Colours::green);
        g.setFont(60.0f);
        g.drawText(note, 0, 0,  getWidth(), getHeight(), juce::Justification::centred, 40.f);
        horizontalTunerBar.repaint();

    }

    void setNote(juce::String note) 
    {
        this->note = note;
    }

    void setCents(float cents)
    {
        horizontalTunerBar.setCents(cents);
    }

    void resize()
    {
        int localX = getLocalBounds().getX();
        int localY = getLocalBounds().getY();
        int localHeight = getLocalBounds().getHeight();
        int localWidth = getLocalBounds().getWidth();
        int margin = 10;
        horizontalTunerBar.setBounds(localX + margin , localY + localHeight*4/5- margin, 
                                    localWidth - 2 * margin, localHeight/5);
    }
private:
    juce::String note;
    float cents;
    HorizontalTunerBarComponent horizontalTunerBar;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TunerBoxComponent)
};
