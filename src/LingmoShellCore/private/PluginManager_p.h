#pragma once

#include "LingmoShellCore/PluginManager.h"

#include <QtCore/QMap>

namespace Lingmo {

class PluginManagerPrivate
{
public:
    QMap<QString, PluginManager::PluginInfo> plugins;
};

} // namespace Lingmo
