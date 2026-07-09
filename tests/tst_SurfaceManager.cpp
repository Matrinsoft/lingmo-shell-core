#include <LingmoShellCore/SurfaceManager.h>

#include <QSignalSpy>
#include <QTest>

class tst_SurfaceManager : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void registerSurface();
    void unregisterSurface();
    void surfaceReady();
    void surfaceByType();
    void duplicateRegister();
};

void tst_SurfaceManager::registerSurface()
{
    auto *mgr = Lingmo::SurfaceManager::instance();
    QSignalSpy regSpy(mgr, &Lingmo::SurfaceManager::surfaceRegistered);
    QVERIFY(regSpy.isValid());

    bool result = mgr->registerSurface(
        QStringLiteral("panel-0"),
        Lingmo::SurfaceManager::SurfaceType::Panel,
        QStringLiteral("lingmo-panel"),
        1234);
    QVERIFY(result);
    QCOMPARE(mgr->surfaceCount(), 1);
    QCOMPARE(regSpy.count(), 1);

    mgr->unregisterSurface(QStringLiteral("panel-0"));
}

void tst_SurfaceManager::unregisterSurface()
{
    auto *mgr = Lingmo::SurfaceManager::instance();
    mgr->registerSurface(
        QStringLiteral("desktop"),
        Lingmo::SurfaceManager::SurfaceType::Desktop,
        QStringLiteral("lingmo-desktop"),
        5678);

    QSignalSpy unregSpy(mgr, &Lingmo::SurfaceManager::surfaceUnregistered);
    QVERIFY(unregSpy.isValid());

    bool result = mgr->unregisterSurface(QStringLiteral("desktop"));
    QVERIFY(result);
    QCOMPARE(mgr->surfaceCount(), 0);
    QCOMPARE(unregSpy.count(), 1);
}

void tst_SurfaceManager::surfaceReady()
{
    auto *mgr = Lingmo::SurfaceManager::instance();
    mgr->registerSurface(
        QStringLiteral("test-surface"),
        Lingmo::SurfaceManager::SurfaceType::Panel,
        QStringLiteral("test"),
        9999);

    QSignalSpy readySpy(mgr, &Lingmo::SurfaceManager::surfaceReadyChanged);
    QVERIFY(readySpy.isValid());

    QVERIFY(!mgr->isSurfaceReady(QStringLiteral("test-surface")));

    mgr->setSurfaceReady(QStringLiteral("test-surface"), true);
    QVERIFY(mgr->isSurfaceReady(QStringLiteral("test-surface")));
    QCOMPARE(readySpy.count(), 1);

    mgr->unregisterSurface(QStringLiteral("test-surface"));
}

void tst_SurfaceManager::surfaceByType()
{
    auto *mgr = Lingmo::SurfaceManager::instance();
    mgr->registerSurface(
        QStringLiteral("panel-0"),
        Lingmo::SurfaceManager::SurfaceType::Panel,
        QStringLiteral("lingmo-panel"),
        1111);
    mgr->registerSurface(
        QStringLiteral("desktop"),
        Lingmo::SurfaceManager::SurfaceType::Desktop,
        QStringLiteral("lingmo-desktop"),
        2222);

    auto panels = mgr->surfacesByType(Lingmo::SurfaceManager::SurfaceType::Panel);
    QCOMPARE(panels.size(), 1);
    QCOMPARE(panels[0].id, QStringLiteral("panel-0"));

    auto desktops = mgr->surfacesByType(Lingmo::SurfaceManager::SurfaceType::Desktop);
    QCOMPARE(desktops.size(), 1);

    mgr->unregisterSurface(QStringLiteral("panel-0"));
    mgr->unregisterSurface(QStringLiteral("desktop"));
}

void tst_SurfaceManager::duplicateRegister()
{
    auto *mgr = Lingmo::SurfaceManager::instance();
    mgr->registerSurface(
        QStringLiteral("dup-test"),
        Lingmo::SurfaceManager::SurfaceType::Panel,
        QStringLiteral("test"),
        3333);

    bool result = mgr->registerSurface(
        QStringLiteral("dup-test"),
        Lingmo::SurfaceManager::SurfaceType::Panel,
        QStringLiteral("test2"),
        4444);
    QVERIFY(!result);

    mgr->unregisterSurface(QStringLiteral("dup-test"));
}

QTEST_MAIN(tst_SurfaceManager)
#include "tst_SurfaceManager.moc"
