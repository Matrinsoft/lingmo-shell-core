#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantMap>
#include <memory>

namespace Lingmo {

class SurfaceManagerPrivate;

//! @brief Manages shell surface registration and lifecycle.
class LINGMOSHELLCORE_EXPORT SurfaceManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(SurfaceManager)

public:
    enum class SurfaceType {
        Panel,
        Desktop,
        Overview,
        Notification,
        Runner
    };
    Q_ENUM(SurfaceType)

    struct SurfaceInfo {
        QString id;
        SurfaceType type;
        QString processName;
        quint32 pid;
        bool ready;
    };

    static SurfaceManager *instance();

    bool registerSurface(const QString &id, SurfaceType type, const QString &processName, quint32 pid);
    bool unregisterSurface(const QString &id);

    QList<SurfaceInfo> surfaceList() const;
    QList<SurfaceInfo> surfacesByType(SurfaceType type) const;

    bool isSurfaceReady(const QString &id) const;
    void setSurfaceReady(const QString &id, bool ready);

    int surfaceCount() const;
    int readySurfaceCount() const;

Q_SIGNALS:
    void surfaceRegistered(const QString &id, SurfaceType type);
    void surfaceUnregistered(const QString &id);
    void surfaceReadyChanged(const QString &id, bool ready);
    void allSurfacesReady();

private:
    SurfaceManager(QObject *parent = nullptr);
    ~SurfaceManager();

    std::unique_ptr<SurfaceManagerPrivate> d;
};

} // namespace Lingmo
