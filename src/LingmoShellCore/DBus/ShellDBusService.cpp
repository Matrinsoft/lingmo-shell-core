#include "LingmoShellCore/ShellDBusService.h"
#include "private/ShellDBusService_p.h"

#include <QDBusConnection>
#include <QDebug>

namespace Lingmo {

ShellDBusService *ShellDBusService::instance()
{
    static ShellDBusService s_instance;
    return &s_instance;
}

ShellDBusService::ShellDBusService(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ShellDBusServicePrivate>())
{
}

ShellDBusService::~ShellDBusService()
{
    unregisterService();
}

bool ShellDBusService::registerService()
{
    if (d->registered) {
        return true;
    }

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (!bus.registerService(QStringLiteral("org.lingmo.Shell"))) {
        qWarning() << "ShellDBusService: failed to register service:"
                    << bus.lastError().message();
        return false;
    }

    if (!bus.registerObject(QStringLiteral("/org/lingmo/Shell"),
                           this,
                           QDBusConnection::ExportScriptableSlots |
                           QDBusConnection::ExportScriptableSignals)) {
        qWarning() << "ShellDBusService: failed to register object:"
                    << bus.lastError().message();
        bus.unregisterService(QStringLiteral("org.lingmo.Shell"));
        return false;
    }

    d->registered = true;
    qInfo("ShellDBusService: registered org.lingmo.Shell");
    return true;
}

void ShellDBusService::unregisterService()
{
    if (!d->registered) {
        return;
    }

    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.unregisterObject(QStringLiteral("/org/lingmo/Shell"));
    bus.unregisterService(QStringLiteral("org.lingmo.Shell"));

    d->registered = false;
    qInfo("ShellDBusService: unregistered org.lingmo.Shell");
}

bool ShellDBusService::isRegistered() const
{
    return d->registered;
}

void ShellDBusService::Reload()
{
    qInfo("ShellDBusService: Reload requested");
    Q_EMIT reloadRequested();
}

void ShellDBusService::Quit()
{
    qInfo("ShellDBusService: Quit requested");
    Q_EMIT quitRequested();
}

void ShellDBusService::Restart()
{
    qInfo("ShellDBusService: Restart requested");
    Q_EMIT restartRequested();
}

} // namespace Lingmo
