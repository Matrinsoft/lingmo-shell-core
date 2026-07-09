#pragma once

#include "LingmoShellCore/SurfaceManager.h"

#include <QtCore/QMap>

namespace Lingmo {

class SurfaceManagerPrivate
{
public:
    QMap<QString, SurfaceManager::SurfaceInfo> surfaces;
};

} // namespace Lingmo
