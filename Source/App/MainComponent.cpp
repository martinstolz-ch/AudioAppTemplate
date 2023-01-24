/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(400, 200);
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
