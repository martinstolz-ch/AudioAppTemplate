/**
 * (c) martin stolz @ noizplay
 */

#pragma once

#include <JuceHeader.h>

namespace aa::cmakeVar {

static constexpr std::string

    buildYear {"@buildYear@"},

    companyName {"@companyName@"},
    companyURL {"@companyURL@"},

    projectVersion {"@PROJECT_VERSION@"},
    projectName {"@PROJECT_NAME@"};

}
