/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#include <JuceHeader.h>

#include "App/MainWindow.h"

class AudioApp : public juce::JUCEApplication {
public:
    AudioApp()= default;

    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String& /*commandLine*/) override {
        mainWindow = std::make_unique<MainWindow>(getApplicationName() + " / " + getApplicationVersion());
        mainWindow->setVisible(true);
    }

    void shutdown() override {
        mainWindow.reset();
    }

    void systemRequestedQuit() override {
        quit();
    }

    void anotherInstanceStarted(const juce::String& /*commandLine*/) override {}

private:
    std::unique_ptr<MainWindow> mainWindow;

};

START_JUCE_APPLICATION( AudioApp )
