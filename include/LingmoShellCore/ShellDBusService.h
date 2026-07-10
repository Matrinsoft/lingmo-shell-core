#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <memory>

namespace Lingmo {

class ShellDBusServicePrivate;

//! @brief D-Bus service providing org.lingmo.Shell interface.
class LINGMOSHELLCORE_EXPORT ShellDBusService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ShellDBusService)

public:
    static ShellDBusService *instance();

    bool registerService();
    void unregisterService();

    bool isRegistered() const;

Q_SIGNALS:
    void reloadRequested();
    void quitRequested();
    void restartRequested();

public Q_SLOTS:
    void Reload();
    void Quit();
    void Restart();

private:
    ShellDBusService(QObject *parent = nullptr);
    ~ShellDBusService();

    std::unique_ptr<ShellDBusServicePrivate> d;
};

} // namespace Lingmo
