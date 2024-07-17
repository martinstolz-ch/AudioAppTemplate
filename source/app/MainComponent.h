/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#pragma once

#include <JuceHeader.h>

#include "../etc/cmakeVar.h"
#include "../etc/appConfig.h"


class MainComponent : public juce::AudioAppComponent {
public:
    MainComponent() {

        setSize(400, 200);

        ///

        // Some platforms require permissions to open input channels so request that here
        if ( juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
             &&
             ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio)) {

            juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                               [&] (bool granted) {
                                                   setAudioChannels (granted ? 2 : 0, 2);
                                               }

            );
        } else {

            // Specify the number of input and output channels that we want to open
            setAudioChannels (2, 2);
        }
    }

    ~MainComponent() override {
        shutdownAudio();
    }

    void paint(juce::Graphics& g) override {
        g.setColour(app_config::MAIN_COLOUR);
        g.setFont (FontOptions().withStyle ("light"));
        g.drawFittedText(
                cmakeVar::companyURL,
                getLocalBounds(),
                juce::Justification::centredBottom,
                1);
    }

    void resized() override {}

    ///

    void prepareToPlay (int /* samplesPerBlockExpected */, double /* sampleRate */) override {
        // ...
    }

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override {
        bufferToFill.clearActiveBufferRegion();
    }

    void releaseResources() override {
        // ...
    }

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )
};
