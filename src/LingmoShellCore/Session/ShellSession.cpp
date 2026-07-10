#include "LingmoShellCore/ShellSession.h"
#include "private/ShellSession_p.h"

#include <QDebug>

namespace Lingmo {

ShellSession *ShellSession::instance()
{
    static ShellSession s_instance;
    return &s_instance;
}

ShellSession::ShellSession(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ShellSessionPrivate>())
{
}

ShellSession::~ShellSession() = default;

bool ShellSession::connectToSession()
{
    if (d->connected) {
        return true;
    }

    qInfo("ShellSession: connecting to session...");
    d->connected = true;
    return true;
}

void ShellSession::disconnectFromSession()
{
    if (!d->connected) {
        return;
    }

    qInfo("ShellSession: disconnecting from session");
    d->connected = false;
}

bool ShellSession::isConnected() const
{
    return d->connected;
}

void ShellSession::Lock()
{
    qInfo("ShellSession: Lock requested");
    Q_EMIT sessionLocked();
}

void ShellSession::Logout()
{
    qInfo("ShellSession: Logout requested");
    Q_EMIT logoutRequested();
}

void ShellSession::Shutdown()
{
    qInfo("ShellSession: Shutdown requested");
    Q_EMIT shutdownRequested();
}

void ShellSession::Reboot()
{
    qInfo("ShellSession: Reboot requested");
    Q_EMIT rebootRequested();
}

} // namespace Lingmo
