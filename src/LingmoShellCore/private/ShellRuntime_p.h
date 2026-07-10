#pragma once

#include "LingmoShellCore/ShellRuntime.h"

namespace Lingmo {

class ShellRuntimePrivate
{
public:
    ShellRuntime *q = nullptr;
    ShellRuntime::State state = ShellRuntime::State::Idle;

    void setState(ShellRuntime::State newState);
};

} // namespace Lingmo
