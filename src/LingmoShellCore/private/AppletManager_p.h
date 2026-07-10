#pragma once

#include "LingmoShellCore/AppletManager.h"

#include <QtCore/QMap>

namespace Lingmo {

class AppletManagerPrivate
{
public:
    QMap<QString, AppletManager::AppletInfo> applets;
};

} // namespace Lingmo
