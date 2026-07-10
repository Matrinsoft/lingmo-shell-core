#pragma once

#include "LingmoShellCore/ThemeWatcher.h"

#include <QtCore/QString>

namespace Lingmo {

class ThemeWatcherPrivate
{
public:
    bool watching = false;
    QString currentTheme;
};

} // namespace Lingmo
