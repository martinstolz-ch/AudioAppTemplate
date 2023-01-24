/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(400, 200);

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

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::prepareToPlay ( int /* samplesPerBlockExpected */, double /* sampleRate */ ) {
    // ...
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    bufferToFill.clearActiveBufferRegion();

    // ...
}

void MainComponent::releaseResources() {
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::paint(Graphics& gContext) {
    gContext.setColour(Config::MAIN_COLOUR);
    gContext.setFont(
            {
                    Config::DEFAULT_TEXT_SIZE,
                    juce::Font::FontStyleFlags::plain }
    );
    gContext.drawFittedText(
            CMakeVars::COMPANY_WEBSITE,
            getLocalBounds(),
            juce::Justification::centredBottom,
            1);
}

void MainComponent::resized() {}
