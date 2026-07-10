#include "LingmoShellCore/AppletManager.h"
#include "private/AppletManager_p.h"

#include <QDebug>

namespace Lingmo {

AppletManager *AppletManager::instance()
{
    static AppletManager s_instance;
    return &s_instance;
}

AppletManager::AppletManager(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<AppletManagerPrivate>())
{
}

AppletManager::~AppletManager() = default;

bool AppletManager::loadApplets()
{
    qInfo("AppletManager: loading all applets...");
    Q_EMIT allAppletsLoaded();
    return true;
}

void AppletManager::unloadApplets()
{
    qInfo("AppletManager: unloading all applets...");
    for (auto it = d->applets.begin(); it != d->applets.end(); ++it) {
        if (it->loaded) {
            it->loaded = false;
            Q_EMIT appletUnloaded(it->id);
        }
    }
}

bool AppletManager::loadApplet(const QString &id)
{
    auto it = d->applets.find(id);
    if (it == d->applets.end()) {
        qWarning() << "AppletManager: applet not found:" << id;
        return false;
    }

    if (it->loaded) {
        qWarning() << "AppletManager: applet already loaded:" << id;
        return false;
    }

    it->loaded = true;
    qInfo("AppletManager: loaded applet '%s'", qPrintable(id));
    Q_EMIT appletLoaded(id);
    return true;
}

bool AppletManager::unloadApplet(const QString &id)
{
    auto it = d->applets.find(id);
    if (it == d->applets.end()) {
        qWarning() << "AppletManager: applet not found:" << id;
        return false;
    }

    if (!it->loaded) {
        return false;
    }

    it->loaded = false;
    qInfo("AppletManager: unloaded applet '%s'", qPrintable(id));
    Q_EMIT appletUnloaded(id);
    return true;
}

QList<AppletManager::AppletInfo> AppletManager::appletList() const
{
    return d->applets.values();
}

int AppletManager::appletCount() const
{
    return d->applets.size();
}

int AppletManager::loadedAppletCount() const
{
    int count = 0;
    for (auto it = d->applets.cbegin(); it != d->applets.cend(); ++it) {
        if (it->loaded) {
            ++count;
        }
    }
    return count;
}

bool AppletManager::isAppletLoaded(const QString &id) const
{
    auto it = d->applets.find(id);
    return it != d->applets.end() && it->loaded;
}

} // namespace Lingmo
