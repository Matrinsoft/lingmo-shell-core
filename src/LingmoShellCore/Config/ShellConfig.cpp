#include "LingmoShellCore/ShellConfig.h"
#include "private/ShellConfig_p.h"

#include <QDebug>

namespace Lingmo {

ShellConfig *ShellConfig::instance()
{
    static ShellConfig s_instance;
    return &s_instance;
}

ShellConfig::ShellConfig(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ShellConfigPrivate>())
{
}

ShellConfig::~ShellConfig() = default;

bool ShellConfig::load()
{
    qInfo("ShellConfig: loading configuration...");
    // TODO: Integrate with lingmo-config
    return true;
}

void ShellConfig::reload()
{
    qInfo("ShellConfig: reloading configuration...");
    load();
}

QString ShellConfig::shellTheme() const
{
    return d->shellTheme;
}

void ShellConfig::setShellTheme(const QString &theme)
{
    if (d->shellTheme == theme) {
        return;
    }
    d->shellTheme = theme;
    Q_EMIT configChanged(QStringLiteral("shellTheme"));
    Q_EMIT themeChanged(theme);
}

bool ShellConfig::animationsEnabled() const
{
    return d->animationsEnabled;
}

void ShellConfig::setAnimationsEnabled(bool enabled)
{
    if (d->animationsEnabled == enabled) {
        return;
    }
    d->animationsEnabled = enabled;
    Q_EMIT configChanged(QStringLiteral("animationsEnabled"));
}

int ShellConfig::panelHeight() const
{
    return d->panelHeight;
}

void ShellConfig::setPanelHeight(int height)
{
    if (d->panelHeight == height) {
        return;
    }
    d->panelHeight = height;
    Q_EMIT configChanged(QStringLiteral("panelHeight"));
}

} // namespace Lingmo
