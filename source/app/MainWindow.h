/**
 * (c) martin stolz @ noizplay
 */

#pragma once

#include <JuceHeader.h>

#include "MainComponent.h"

namespace aa {

constexpr bool isMobile() {
#if JUCE_IOS || JUCE_ANDROID
    return true;
#else
    return false;
#endif
}

class MainWindow final
    : public DocumentWindow {

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
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

    static Colour getBackgroundColour() {
        return Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    }
};

}