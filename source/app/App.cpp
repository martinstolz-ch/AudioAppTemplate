/**
 * (c) martin stolz @ noizplay
 */

#include <JuceHeader.h>

#include "MainWindow.h"

namespace aa {

class AudioApp final
    : public JUCEApplication {

public:
    AudioApp()= default;

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const String& /*commandLine*/) override {
        mainWindow = std::make_unique<MainWindow>(getApplicationName() + " / " + getApplicationVersion());
        mainWindow->setVisible(true);
    }

    void shutdown() override {
        mainWindow.reset();
    }

    void systemRequestedQuit() override {
        quit();
    }

    void anotherInstanceStarted(const String& /*commandLine*/) override {}

private:
    std::unique_ptr<MainWindow> mainWindow;

};

}

START_JUCE_APPLICATION( aa::AudioApp )
