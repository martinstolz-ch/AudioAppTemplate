/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#include "MainWindow.h"

constexpr bool isMobile() {
    #if JUCE_IOS || JUCE_ANDROID
        return true;
    #else
        return false;
    #endif
}

MainWindow::MainWindow(const String& name):
        DocumentWindow(name, getBackgroundColour(), allButtons) {

    setUsingNativeTitleBar(true);
    setContentOwned(new MainComponent(), true);

    if (isMobile()) {
        setFullScreen(true);
    }
    else {
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
    }

    setVisible(true);
}

void MainWindow::closeButtonPressed() {
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

Colour MainWindow::getBackgroundColour() {
    return juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId);
}

