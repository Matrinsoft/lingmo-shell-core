#include <LingmoShellCore/AppletManager.h>

#include <QSignalSpy>
#include <QTest>

class tst_AppletManager : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void loadApplets();
    void loadUnload();
    void appletCount();
};

void tst_AppletManager::loadApplets()
{
    auto *mgr = Lingmo::AppletManager::instance();
    QSignalSpy loadedSpy(mgr, &Lingmo::AppletManager::allAppletsLoaded);
    QVERIFY(loadedSpy.isValid());

    bool result = mgr->loadApplets();
    QVERIFY(result);
    QCOMPARE(loadedSpy.count(), 1);
}

void tst_AppletManager::loadUnload()
{
    auto *mgr = Lingmo::AppletManager::instance();

    // Test with non-existent applet
    bool result = mgr->loadApplet(QStringLiteral("nonexistent"));
    QVERIFY(!result);
}

void tst_AppletManager::appletCount()
{
    auto *mgr = Lingmo::AppletManager::instance();
    int count = mgr->appletCount();
    QVERIFY(count >= 0);
}

QTEST_MAIN(tst_AppletManager)
#include "tst_AppletManager.moc"
