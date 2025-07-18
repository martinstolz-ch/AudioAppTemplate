#################################################
# (c) martin stolz @ noizplay
#################################################

# preconditions
cmake_minimum_required (VERSION 3.31.3)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON) # ON: use "-std=gnu++20" / OFF: use "-std=c++20"

# install vcpkg package manager in "~/Library/vcpkg"
# (NOT in /opt/vcpkg -> will result in permission confusion!):
#
# cd ~/Library
# git clone https://github.com/microsoft/vcpkg.git ~/Library/vcpkg
# ~/Library/vcpkg/bootstrap-vcpkg.sh
#
# add vcpkg folder to PATH in ~/.zshrc
#
# export PATH="$PATH:$HOME/Library/vcpkg"

# setup the vcpkg toolchain for cmake
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    find_program(VCPKG_EXECUTABLE vcpkg)
    if(VCPKG_EXECUTABLE)
        get_filename_component(VCPKG_ROOT ${VCPKG_EXECUTABLE} DIRECTORY)
        set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
        message(STATUS "Using vcpkg: ${VCPKG_ROOT}")
    endif()
endif()


# project config ################################
project (AUDIO_APP VERSION 0.0.1)
set     (Target      ${PROJECT_NAME})
set     (ProductName "Audio App")

set (companyName "noizplay")
set (companyURL "noizplay.com")

unset  (USE_BOOST CACHE)
option (USE_BOOST "Enable Boost libraries" ON)
#################################################


# initialise
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile_commands.json")
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


# fetch external repos directly from github
include(FetchContent)

message (STATUS "fetch juce")
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.8
)
FetchContent_MakeAvailable(JUCE)

# install required pack(s) for the 1st time:
#
# vcpkg install boost-spirit boost-fusion boost-core
if (USE_BOOST)
    find_package (Boost REQUIRED CONFIG)
    message (STATUS "Boost version: ${Boost_VERSION}")
endif ()

# define JUCE app
juce_add_gui_app (${Target}
    # ICON_BIG        "..."
    # ICON_SMALL      "..."
    PRODUCT_NAME    "${ProductName}"
    COMPANY_NAME    "${companyName}"
    COMPANY_WEBSITE "${companyURL}"
)

juce_generate_juce_header("${Target}")

target_sources("${Target}"
    PUBLIC
    source/app/App.cpp
)

# link libraries
target_link_libraries("${Target}"
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_utils
    juce::juce_graphics
    juce::juce_gui_basics

    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

if (USE_BOOST)
    target_link_libraries("${Target}"
        PRIVATE
        Boost::boost
    )
endif ()

target_compile_definitions ("${Target}"
    PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${Target},JUCE_PROJECT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${Target},JUCE_VERSION>"
)

# create cmakeVars.h
target_include_directories(${Target} PRIVATE "${CMAKE_BINARY_DIR}/source/common")
get_target_property (COMPANY_WEBSITE ${Target} JUCE_COMPANY_WEBSITE)
string (TIMESTAMP buildYear "%Y")
configure_file (template/cmakeVar.h.tpl "source/common/cmakeVar.h" )
