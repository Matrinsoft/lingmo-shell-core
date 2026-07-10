#include <LingmoShellCore/PluginManager.h>

#include <QSignalSpy>
#include <QTest>

class tst_PluginManager : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void loadPlugins();
    void loadUnload();
    void pluginsByType();
};

void tst_PluginManager::loadPlugins()
{
    auto *mgr = Lingmo::PluginManager::instance();
    QSignalSpy loadedSpy(mgr, &Lingmo::PluginManager::allPluginsLoaded);
    QVERIFY(loadedSpy.isValid());

    bool result = mgr->loadPlugins();
    QVERIFY(result);
    QCOMPARE(loadedSpy.count(), 1);
}

void tst_PluginManager::loadUnload()
{
    auto *mgr = Lingmo::PluginManager::instance();
    QSignalSpy loadSpy(mgr, &Lingmo::PluginManager::pluginLoaded);
    QVERIFY(loadSpy.isValid());

    // Test with non-existent plugin
    bool result = mgr->loadPlugin(QStringLiteral("nonexistent"));
    QVERIFY(!result);
}

void tst_PluginManager::pluginsByType()
{
    auto *mgr = Lingmo::PluginManager::instance();
    auto applets = mgr->pluginsByType(Lingmo::PluginManager::PluginType::Applet);
    auto extensions = mgr->pluginsByType(Lingmo::PluginManager::PluginType::ShellExtension);
    // Should not crash
    QVERIFY(true);
}

QTEST_MAIN(tst_PluginManager)
#include "tst_PluginManager.moc"
