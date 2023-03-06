/**
 * created by Martin Stolz on 08.10.22
 *
 * (c) 2022 by noizplay.com
 */

#pragma once

#include <JuceHeader.h>

namespace cmake_vars {

    #define DECLARE_VAR(name, val) const std::string name{val};

    DECLARE_VAR(COMPANY_WEBSITE, "noizplay.com")
    DECLARE_VAR(PROJECT_VERSION, "0.0.1")

    #undef DECLARE_VAR

}
