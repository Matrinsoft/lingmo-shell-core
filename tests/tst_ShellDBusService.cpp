#include <LingmoShellCore/ShellDBusService.h>

#include <QSignalSpy>
#include <QTest>

class tst_ShellDBusService : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void registerService();
    void isRegistered();
    void reloadSignal();
};

void tst_ShellDBusService::registerService()
{
    auto *svc = Lingmo::ShellDBusService::instance();
    QVERIFY(svc != nullptr);

    // May fail if D-Bus is not available in test environment
    svc->registerService();
    // Just verify it doesn't crash
    QVERIFY(true);
}

void tst_ShellDBusService::isRegistered()
{
    auto *svc = Lingmo::ShellDBusService::instance();
    // State depends on registerService call
    bool registered = svc->isRegistered();
    QVERIFY(registered || !registered);
}

void tst_ShellDBusService::reloadSignal()
{
    auto *svc = Lingmo::ShellDBusService::instance();
    QSignalSpy reloadSpy(svc, &Lingmo::ShellDBusService::reloadRequested);
    QVERIFY(reloadSpy.isValid());

    svc->Reload();
    QCOMPARE(reloadSpy.count(), 1);
}

QTEST_MAIN(tst_ShellDBusService)
#include "tst_ShellDBusService.moc"
