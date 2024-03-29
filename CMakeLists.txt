cmake_minimum_required(VERSION 3.16)

set (CMAKE_CXX_STANDARD 20)


#########################################################################
project (AUDIO_APP VERSION 0.0.1)
set     (TargetName   AudioApp)
set     (ProductName "Audio App")
#########################################################################


# use CPM
include(cmake/CPM.cmake)
set(CPM_USE_NAMED_CACHE_DIRECTORIES true)
set(CPM_SOURCE_CACHE ~/.cache/CPM)

# get JUCE
CPMAddPackage("gh:juce-framework/JUCE@7.0.11#master")

# Compile commands, useful for some IDEs like VS-Code
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Minimum MacOS target, set globally
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum OS X deployment version" FORCE)

# Universal Binary ?
option(UniversalBinary "Build universal binary for mac" ON)

if (UniversalBinary)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "")
    set(MACOSX_BUNDLE TRUE)
endif()

# static linking in Windows
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Adds all the module sources so they appear correctly in the IDE
set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

juce_add_gui_app(${TargetName}
    # VERSION ...                        # Set this if the app version is different to the project version
    # ICON_BIG ...
    # ICON_SMALL ...
    PRODUCT_NAME "${ProductName}"
    COMPANY_NAME "noizplay"
    COMPANY_WEBSITE "noizplay.com"
)

juce_generate_juce_header("${TargetName}")

target_sources("${TargetName}"
    PRIVATE
        Source/App.cpp
)

target_compile_definitions("${TargetName}"
    PRIVATE
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_PROJECT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_VERSION>"
)

target_link_libraries("${TargetName}"
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_utils
        juce::juce_graphics
        juce::juce_gui_basics

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# get some JUCE properties
get_target_property(JUCE_COMPANY_WEBSITE ${TargetName} JUCE_COMPANY_WEBSITE)

# export some vars to CMakeVars.h in /Source folder
configure_file(CMakeVars.h.in "${CMAKE_CURRENT_SOURCE_DIR}/Source/Common/CMakeVars.h" )
