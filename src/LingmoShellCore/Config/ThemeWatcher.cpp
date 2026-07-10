#include "LingmoShellCore/ThemeWatcher.h"
#include "private/ThemeWatcher_p.h"

#include <QDebug>

namespace Lingmo {

ThemeWatcher *ThemeWatcher::instance()
{
    static ThemeWatcher s_instance;
    return &s_instance;
}

ThemeWatcher::ThemeWatcher(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ThemeWatcherPrivate>())
{
}

ThemeWatcher::~ThemeWatcher()
{
    stopWatching();
}

bool ThemeWatcher::startWatching()
{
    if (d->watching) {
        return true;
    }

    qInfo("ThemeWatcher: starting to watch theme changes...");
    d->watching = true;
    return true;
}

void ThemeWatcher::stopWatching()
{
    if (!d->watching) {
        return;
    }

    qInfo("ThemeWatcher: stopping theme watch");
    d->watching = false;
}

QString ThemeWatcher::currentTheme() const
{
    return d->currentTheme;
}

bool ThemeWatcher::isWatching() const
{
    return d->watching;
}

} // namespace Lingmo
