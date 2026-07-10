#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>

namespace Lingmo {

class AppletManagerPrivate;

//! @brief Manages loading and lifecycle of applet plugins.
class LINGMOSHELLCORE_EXPORT AppletManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AppletManager)

public:
    struct AppletInfo {
        QString id;
        QString name;
        QString description;
        QString icon;
        QString libraryPath;
        bool loaded;
        bool configurable;
    };

    static AppletManager *instance();

    bool loadApplets();
    void unloadApplets();

    bool loadApplet(const QString &id);
    bool unloadApplet(const QString &id);

    QList<AppletInfo> appletList() const;
    int appletCount() const;
    int loadedAppletCount() const;

    bool isAppletLoaded(const QString &id) const;

Q_SIGNALS:
    void appletLoaded(const QString &id);
    void appletUnloaded(const QString &id);
    void allAppletsLoaded();

private:
    AppletManager(QObject *parent = nullptr);
    ~AppletManager();

    std::unique_ptr<AppletManagerPrivate> d;
};

} // namespace Lingmo
