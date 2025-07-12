/**
 * (c) martin stolz @ noizplay
 */

#pragma once

#include <JuceHeader.h>

namespace aa::cmakeVar {

static const String
    buildYear {"@buildYear@"},

    companyName {"@companyName@"},
    companyURL {"@companyURL@"},

    projectVersion {"@PROJECT_VERSION@"},
    projectName {"@PROJECT_NAME@"};

}
