###############################################################################
# martin stolz - (c) noizplay.com
###############################################################################
cmake_minimum_required (VERSION 3.31.3)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON) # ON: use "-std=gnu++20" / OFF: use "-std=c++20"

find_program(VCPKG_EXECUTABLE vcpkg)
if(VCPKG_EXECUTABLE AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    get_filename_component(VCPKG_ROOT ${VCPKG_EXECUTABLE} DIRECTORY)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

project (AUDIO_APP VERSION 0.0.1)
set     (TargetName    ${PROJECT_NAME})
set     (ProductName  "Audio App")

set (companyName "noizplay")
set (companyURL "noizplay.com")
###############################################################################

# initialise
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property (GLOBAL PROPERTY USE_FOLDERS YES)
option (JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

# we are Mac ?
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set (CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum OS X deployment version" FORCE)
    set (CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE INTERNAL "")
    set (MACOSX_BUNDLE TRUE) # create .app bundle for mac
    message (STATUS "Build for Mac")

    # ...or Win ?
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # static linking in Windows
    message (STATUS "Build for Windows")

    # ...nope :/
else ()
    message (FATAL_ERROR "No viable platform found")
endif ()

# fetch external repos
include(FetchContent)

message (STATUS "Fetch JUCE")
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.8
)
FetchContent_MakeAvailable(JUCE)

# find Boost
# find_package (Boost REQUIRED CONFIG)
# message (STATUS "Boost version: ${Boost_VERSION}")

# define JUCE app
juce_add_gui_app (${TargetName}
    # ICON_BIG        "..."
    # ICON_SMALL      "..."
    PRODUCT_NAME    "${ProductName}"
    COMPANY_NAME    "${companyName}"
    COMPANY_WEBSITE "${companyURL}"
)

juce_generate_juce_header("${TargetName}")

target_sources("${TargetName}"
    PUBLIC
    Source/app/App.cpp
)

target_link_libraries("${TargetName}"
    PRIVATE

    # Boost::boost

    juce::juce_audio_basics
    juce::juce_audio_utils
    juce::juce_graphics
    juce::juce_gui_basics

    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

target_compile_definitions ("${TargetName}"
    PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_PROJECT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_VERSION>"
)

# create cmakeVars.h
get_target_property (COMPANY_WEBSITE ${TargetName} JUCE_COMPANY_WEBSITE)
string (TIMESTAMP buildYear "%Y")
configure_file (template/cmakeVar.h.tpl "source/common/cmakeVar.h" )
