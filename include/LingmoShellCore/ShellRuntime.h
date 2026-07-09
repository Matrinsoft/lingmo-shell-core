#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <memory>

namespace Lingmo {

class ShellRuntimePrivate;

//! @brief Shell runtime core managing lifecycle and initialization.
class LINGMOSHELLCORE_EXPORT ShellRuntime : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ShellRuntime)

public:
    enum class State {
        Idle,
        Initializing,
        Running,
        ShuttingDown,
        Stopped
    };
    Q_ENUM(State)

    static ShellRuntime *instance();

    State state() const;

    bool initialize();
    void shutdown();
    void restart();

    bool isRunning() const;

Q_SIGNALS:
    void stateChanged(State oldState, State newState);
    void ready();
    void aboutToQuit();

private:
    ShellRuntime(QObject *parent = nullptr);
    ~ShellRuntime();

    std::unique_ptr<ShellRuntimePrivate> d;
};

} // namespace Lingmo
