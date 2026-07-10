#pragma once

#include "LingmoShellCore/ShellConfig.h"

#include <QtCore/QString>

namespace Lingmo {

class ShellConfigPrivate
{
public:
    QString shellTheme = QStringLiteral("default");
    bool animationsEnabled = true;
    int panelHeight = 32;
};

} // namespace Lingmo
