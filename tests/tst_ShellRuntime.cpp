#include <LingmoShellCore/ShellRuntime.h>

#include <QSignalSpy>
#include <QTest>

class tst_ShellRuntime : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initialState();
    void initialize();
    void shutdown();
    void stateSignals();
};

void tst_ShellRuntime::initialState()
{
    auto *runtime = Lingmo::ShellRuntime::instance();
    QVERIFY(runtime != nullptr);
    // After previous tests may have initialized, check if not crashed
}

void tst_ShellRuntime::initialize()
{
    auto *runtime = Lingmo::ShellRuntime::instance();
    QSignalSpy readySpy(runtime, &Lingmo::ShellRuntime::ready);
    QVERIFY(readySpy.isValid());

    bool result = runtime->initialize();
    QVERIFY(result);
    QVERIFY(runtime->isRunning());
    QCOMPARE(readySpy.count(), 1);
}

void tst_ShellRuntime::shutdown()
{
    auto *runtime = Lingmo::ShellRuntime::instance();
    QSignalSpy quitSpy(runtime, &Lingmo::ShellRuntime::aboutToQuit);
    QVERIFY(quitSpy.isValid());

    runtime->shutdown();
    QVERIFY(!runtime->isRunning());
    QCOMPARE(quitSpy.count(), 1);
}

void tst_ShellRuntime::stateSignals()
{
    auto *runtime = Lingmo::ShellRuntime::instance();
    QSignalSpy stateSpy(runtime, &Lingmo::ShellRuntime::stateChanged);
    QVERIFY(stateSpy.isValid());

    runtime->initialize();
    QVERIFY(stateSpy.count() >= 1);

    runtime->shutdown();
    QVERIFY(stateSpy.count() >= 2);
}

QTEST_MAIN(tst_ShellRuntime)
#include "tst_ShellRuntime.moc"
