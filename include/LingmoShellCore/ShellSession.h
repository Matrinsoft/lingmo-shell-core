#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <memory>

namespace Lingmo {

class ShellSessionPrivate;

//! @brief Session integration for shell-core (login/logout/lock/shutdown).
class LINGMOSHELLCORE_EXPORT ShellSession : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ShellSession)

public:
    static ShellSession *instance();

    bool connectToSession();
    void disconnectFromSession();

    bool isConnected() const;

Q_SIGNALS:
    void sessionLocked();
    void sessionUnlocked();
    void logoutRequested();
    void shutdownRequested();
    void rebootRequested();

public Q_SLOTS:
    void Lock();
    void Logout();
    void Shutdown();
    void Reboot();

private:
    ShellSession(QObject *parent = nullptr);
    ~ShellSession();

    std::unique_ptr<ShellSessionPrivate> d;
};

} // namespace Lingmo
