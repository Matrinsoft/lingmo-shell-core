#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>

namespace Lingmo {

class ThemeWatcherPrivate;

//! @brief Watches for theme changes and notifies surfaces.
class LINGMOSHELLCORE_EXPORT ThemeWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ThemeWatcher)

public:
    static ThemeWatcher *instance();

    bool startWatching();
    void stopWatching();

    QString currentTheme() const;
    bool isWatching() const;

Q_SIGNALS:
    void themeChanged(const QString &newTheme);
    void themeReloadRequested();

private:
    ThemeWatcher(QObject *parent = nullptr);
    ~ThemeWatcher();

    std::unique_ptr<ThemeWatcherPrivate> d;
};

} // namespace Lingmo
