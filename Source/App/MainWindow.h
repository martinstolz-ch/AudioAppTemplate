/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#pragma once

#include "MainComponent.h"

using namespace std;

class MainWindow : public juce::DocumentWindow {
public:
    MainWindow(const juce::String& name);

private:
    void closeButtonPressed() override;
    juce::Colour getBackgroundColour();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

