#pragma once

#include <LingmoShellCore/LingmoShellCoreExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>

namespace Lingmo {

class ShellConfigPrivate;

//! @brief Shell configuration management using lingmo-config.
class LINGMOSHELLCORE_EXPORT ShellConfig : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ShellConfig)

public:
    static ShellConfig *instance();

    bool load();
    void reload();

    QString shellTheme() const;
    void setShellTheme(const QString &theme);

    bool animationsEnabled() const;
    void setAnimationsEnabled(bool enabled);

    int panelHeight() const;
    void setPanelHeight(int height);

Q_SIGNALS:
    void configChanged(const QString &key);
    void themeChanged(const QString &theme);

private:
    ShellConfig(QObject *parent = nullptr);
    ~ShellConfig();

    std::unique_ptr<ShellConfigPrivate> d;
};

} // namespace Lingmo
