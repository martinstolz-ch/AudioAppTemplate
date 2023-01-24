/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#include "App/MainWindow.h"

using namespace std;

class App : public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override {
        return ProjectInfo::projectName;
    }
    const juce::String getApplicationVersion() override {
        return ProjectInfo::versionString;
    }
    bool moreThanOneInstanceAllowed() override {
        return true;
    }

    void initialise(const juce::String& /*commandLine*/) override {
        mainWindow = make_unique<MainWindow>(getApplicationName() + " / " + getApplicationVersion());
    }

    void shutdown() override {
        mainWindow.reset();
    }

    void systemRequestedQuit() override {
        quit();
    }

    void anotherInstanceStarted(const juce::String& /*commandLine*/) override {}

private:
    unique_ptr<MainWindow> mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(App)
