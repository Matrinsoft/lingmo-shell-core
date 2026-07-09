#include "LingmoShellCore/SurfaceManager.h"
#include "private/SurfaceManager_p.h"

#include <QDebug>

namespace Lingmo {

SurfaceManager *SurfaceManager::instance()
{
    static SurfaceManager s_instance;
    return &s_instance;
}

SurfaceManager::SurfaceManager(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<SurfaceManagerPrivate>())
{
}

SurfaceManager::~SurfaceManager() = default;

bool SurfaceManager::registerSurface(const QString &id, SurfaceType type, const QString &processName, quint32 pid)
{
    if (d->surfaces.contains(id)) {
        qWarning() << "SurfaceManager: surface already registered:" << id;
        return false;
    }

    SurfaceInfo info;
    info.id = id;
    info.type = type;
    info.processName = processName;
    info.pid = pid;
    info.ready = false;

    d->surfaces.insert(id, info);

    qInfo("SurfaceManager: registered surface '%s' (type=%d, pid=%u)",
          qPrintable(id), static_cast<int>(type), pid);

    Q_EMIT surfaceRegistered(id, type);
    return true;
}

bool SurfaceManager::unregisterSurface(const QString &id)
{
    if (!d->surfaces.remove(id)) {
        qWarning() << "SurfaceManager: surface not found:" << id;
        return false;
    }

    qInfo("SurfaceManager: unregistered surface '%s'", qPrintable(id));
    Q_EMIT surfaceUnregistered(id);
    return true;
}

QList<SurfaceManager::SurfaceInfo> SurfaceManager::surfaceList() const
{
    return d->surfaces.values();
}

QList<SurfaceManager::SurfaceInfo> SurfaceManager::surfacesByType(SurfaceType type) const
{
    QList<SurfaceInfo> result;
    for (auto it = d->surfaces.cbegin(); it != d->surfaces.cend(); ++it) {
        if (it->type == type) {
            result.append(*it);
        }
    }
    return result;
}

bool SurfaceManager::isSurfaceReady(const QString &id) const
{
    auto it = d->surfaces.find(id);
    return it != d->surfaces.end() && it->ready;
}

void SurfaceManager::setSurfaceReady(const QString &id, bool ready)
{
    auto it = d->surfaces.find(id);
    if (it == d->surfaces.end()) {
        qWarning() << "SurfaceManager: surface not found:" << id;
        return;
    }

    if (it->ready == ready) {
        return;
    }

    it->ready = ready;
    Q_EMIT surfaceReadyChanged(id, ready);

    if (ready && readySurfaceCount() == surfaceCount()) {
        Q_EMIT allSurfacesReady();
    }
}

int SurfaceManager::surfaceCount() const
{
    return d->surfaces.size();
}

int SurfaceManager::readySurfaceCount() const
{
    int count = 0;
    for (auto it = d->surfaces.cbegin(); it != d->surfaces.cend(); ++it) {
        if (it->ready) {
            ++count;
        }
    }
    return count;
}

} // namespace Lingmo
