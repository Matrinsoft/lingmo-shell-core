#include <LingmoShellCore/ShellConfig.h>

#include <QSignalSpy>
#include <QTest>

class tst_ShellConfig : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void load();
    void themeChange();
    void panelHeight();
    void animationsEnabled();
};

void tst_ShellConfig::load()
{
    auto *cfg = Lingmo::ShellConfig::instance();
    bool result = cfg->load();
    QVERIFY(result);
}

void tst_ShellConfig::themeChange()
{
    auto *cfg = Lingmo::ShellConfig::instance();
    QSignalSpy themeSpy(cfg, &Lingmo::ShellConfig::themeChanged);
    QVERIFY(themeSpy.isValid());
    QSignalSpy configSpy(cfg, &Lingmo::ShellConfig::configChanged);
    QVERIFY(configSpy.isValid());

    cfg->setShellTheme(QStringLiteral("dark"));
    QCOMPARE(cfg->shellTheme(), QStringLiteral("dark"));
    QCOMPARE(themeSpy.count(), 1);
    QCOMPARE(configSpy.count(), 1);

    // Setting same value should not emit
    cfg->setShellTheme(QStringLiteral("dark"));
    QCOMPARE(themeSpy.count(), 1);
}

void tst_ShellConfig::panelHeight()
{
    auto *cfg = Lingmo::ShellConfig::instance();
    QSignalSpy configSpy(cfg, &Lingmo::ShellConfig::configChanged);
    QVERIFY(configSpy.isValid());

    cfg->setPanelHeight(48);
    QCOMPARE(cfg->panelHeight(), 48);
    QCOMPARE(configSpy.count(), 1);
}

void tst_ShellConfig::animationsEnabled()
{
    auto *cfg = Lingmo::ShellConfig::instance();
    cfg->setAnimationsEnabled(false);
    QVERIFY(!cfg->animationsEnabled());

    cfg->setAnimationsEnabled(true);
    QVERIFY(cfg->animationsEnabled());
}

QTEST_MAIN(tst_ShellConfig)
#include "tst_ShellConfig.moc"
