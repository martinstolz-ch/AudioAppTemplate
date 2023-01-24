/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#pragma once

#include "../Common/CMakeVars.h"
#include "../Common/Config.h"

#include <JuceHeader.h>

class MainComponent : public juce::AudioAppComponent {

public:

    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )
};
