#pragma once

#include "LingmoShellCore/ShellRuntime.h"

namespace Lingmo {

class ShellRuntimePrivate
{
public:
    ShellRuntime::State state = ShellRuntime::State::Idle;

    void setState(ShellRuntime::State newState);
};

} // namespace Lingmo
