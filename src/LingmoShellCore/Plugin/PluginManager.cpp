#include "LingmoShellCore/PluginManager.h"
#include "private/PluginManager_p.h"

#include <QDebug>

namespace Lingmo {

PluginManager *PluginManager::instance()
{
    static PluginManager s_instance;
    return &s_instance;
}

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<PluginManagerPrivate>())
{
}

PluginManager::~PluginManager() = default;

bool PluginManager::loadPlugins()
{
    qInfo("PluginManager: loading all plugins...");
    Q_EMIT allPluginsLoaded();
    return true;
}

void PluginManager::unloadPlugins()
{
    qInfo("PluginManager: unloading all plugins...");
    for (auto it = d->plugins.begin(); it != d->plugins.end(); ++it) {
        if (it->loaded) {
            it->loaded = false;
            Q_EMIT pluginUnloaded(it->id);
        }
    }
}

bool PluginManager::loadPlugin(const QString &id)
{
    auto it = d->plugins.find(id);
    if (it == d->plugins.end()) {
        qWarning() << "PluginManager: plugin not found:" << id;
        return false;
    }

    if (it->loaded) {
        qWarning() << "PluginManager: plugin already loaded:" << id;
        return false;
    }

    it->loaded = true;
    qInfo("PluginManager: loaded plugin '%s'", qPrintable(id));
    Q_EMIT pluginLoaded(id);
    return true;
}

bool PluginManager::unloadPlugin(const QString &id)
{
    auto it = d->plugins.find(id);
    if (it == d->plugins.end()) {
        qWarning() << "PluginManager: plugin not found:" << id;
        return false;
    }

    if (!it->loaded) {
        return false;
    }

    it->loaded = false;
    qInfo("PluginManager: unloaded plugin '%s'", qPrintable(id));
    Q_EMIT pluginUnloaded(id);
    return true;
}

QList<PluginManager::PluginInfo> PluginManager::pluginList() const
{
    return d->plugins.values();
}

QList<PluginManager::PluginInfo> PluginManager::pluginsByType(PluginType type) const
{
    QList<PluginInfo> result;
    for (auto it = d->plugins.cbegin(); it != d->plugins.cend(); ++it) {
        if (it->type == type) {
            result.append(*it);
        }
    }
    return result;
}

bool PluginManager::isPluginLoaded(const QString &id) const
{
    auto it = d->plugins.find(id);
    return it != d->plugins.end() && it->loaded;
}

int PluginManager::loadedPluginCount() const
{
    int count = 0;
    for (auto it = d->plugins.cbegin(); it != d->plugins.cend(); ++it) {
        if (it->loaded) {
            ++count;
        }
    }
    return count;
}

} // namespace Lingmo
