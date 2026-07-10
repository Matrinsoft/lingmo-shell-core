#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>

namespace Lingmo {

class PluginManagerPrivate;

//! @brief Unified plugin manager for applets and shell extensions.
class LINGMOSHELLCORE_EXPORT PluginManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PluginManager)

public:
    enum class PluginType {
        Applet,
        ShellExtension
    };
    Q_ENUM(PluginType)

    struct PluginInfo {
        QString id;
        QString name;
        PluginType type;
        QString libraryPath;
        bool loaded;
    };

    static PluginManager *instance();

    bool loadPlugins();
    void unloadPlugins();

    bool loadPlugin(const QString &id);
    bool unloadPlugin(const QString &id);

    QList<PluginInfo> pluginList() const;
    QList<PluginInfo> pluginsByType(PluginType type) const;

    bool isPluginLoaded(const QString &id) const;
    int loadedPluginCount() const;

Q_SIGNALS:
    void pluginLoaded(const QString &id);
    void pluginUnloaded(const QString &id);
    void allPluginsLoaded();

private:
    PluginManager(QObject *parent = nullptr);
    ~PluginManager();

    std::unique_ptr<PluginManagerPrivate> d;
};

} // namespace Lingmo
