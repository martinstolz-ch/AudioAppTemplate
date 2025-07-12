/**
 * (c) martin stolz @ noizplay
 */

#pragma once

#include <JuceHeader.h>

#include "../common/cmakeVar.h"
#include "../common/appConfig.h"

namespace aa {

class MainComponent final
    : public AudioAppComponent {

public:
    MainComponent() {

        setSize(400, 200);

        ///

        // Some platforms require permissions to open input channels so request that here
        if ( RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
             &&
             ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio)) {

            RuntimePermissions::request (RuntimePermissions::recordAudio,
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

    void paint(Graphics& g) override {
        g.setColour(app_config::MAIN_COLOUR);
        g.setFont (FontOptions().withStyle ("light"));
        g.drawFittedText(
                cmakeVar::companyURL,
                getLocalBounds(),
                Justification::centredBottom,
                1);
    }

    void resized() override {}

    /**
     * Prepares the audio processor for play by setting up the necessary sample rate, block size,
     * and performing any initialization required before audio playback or processing begins.
     *
     * @param sampleRate The sample rate at which the processor will operate, typically in Hz (e.g., 44100, 48000).
     * @param samplesPerBlockExpected The number of samples per audio processing block. This value dictates the buffer size being processed at a time.
     */

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override {
        ignoreUnused(samplesPerBlockExpected, sampleRate); // avoid warning
        // ...
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override {
        ignoreUnused(bufferToFill); // avoid warning
        bufferToFill.clearActiveBufferRegion();
    }

    void releaseResources() override {
        // ...
    }

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )
};

}