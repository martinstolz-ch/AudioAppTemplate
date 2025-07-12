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

}