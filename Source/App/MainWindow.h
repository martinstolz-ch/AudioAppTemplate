/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#pragma once

#include <JuceHeader.h>

#include "MainComponent.h"

constexpr bool isMobile() {
    #if JUCE_IOS || JUCE_ANDROID
        return true;
    #else
        return false;
    #endif
}

class MainWindow : public juce::DocumentWindow {
public:
    explicit MainWindow(const String& name): DocumentWindow(name, getBackgroundColour(), allButtons) {

        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);

        if (isMobile()) {
            setFullScreen(true);
        }
        else {
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
        }
    }

private:
    void closeButtonPressed() override {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }

    static juce::Colour getBackgroundColour() {
        return juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    }
};

