#include "LingmoShellCore/ShellRuntime.h"
#include "private/ShellRuntime_p.h"

#include <QDebug>

namespace Lingmo {

ShellRuntime *ShellRuntime::instance()
{
    static ShellRuntime s_instance;
    return &s_instance;
}

ShellRuntime::ShellRuntime(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ShellRuntimePrivate>())
{
    d->q = this;
}

ShellRuntime::~ShellRuntime() = default;

ShellRuntime::State ShellRuntime::state() const
{
    return d->state;
}

bool ShellRuntime::isRunning() const
{
    return d->state == State::Running;
}

bool ShellRuntime::initialize()
{
    if (d->state != State::Idle) {
        qWarning() << "ShellRuntime: cannot initialize in state" << d->state;
        return false;
    }

    d->setState(State::Initializing);

    qInfo("ShellRuntime: initializing...");

    Q_EMIT ready();
    d->setState(State::Running);

    qInfo("ShellRuntime: ready");
    return true;
}

void ShellRuntime::shutdown()
{
    if (d->state == State::Idle || d->state == State::Stopped) {
        return;
    }

    d->setState(State::ShuttingDown);
    qInfo("ShellRuntime: shutting down...");

    Q_EMIT aboutToQuit();
    d->setState(State::Stopped);

    qInfo("ShellRuntime: stopped");
}

void ShellRuntime::restart()
{
    shutdown();
    initialize();
}

void ShellRuntimePrivate::setState(ShellRuntime::State newState)
{
    auto oldState = state;
    state = newState;
    Q_EMIT q->stateChanged(oldState, newState);
}

} // namespace Lingmo
