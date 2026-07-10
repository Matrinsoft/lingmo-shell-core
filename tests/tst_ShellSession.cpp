#include <LingmoShellCore/ShellSession.h>

#include <QSignalSpy>
#include <QTest>

class tst_ShellSession : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void connectDisconnect();
    void lockSignal();
    void logoutSignal();
    void shutdownSignal();
    void rebootSignal();
};

void tst_ShellSession::connectDisconnect()
{
    auto *session = Lingmo::ShellSession::instance();
    QVERIFY(!session->isConnected());

    bool result = session->connectToSession();
    QVERIFY(result);
    QVERIFY(session->isConnected());

    session->disconnectFromSession();
    QVERIFY(!session->isConnected());
}

void tst_ShellSession::lockSignal()
{
    auto *session = Lingmo::ShellSession::instance();
    QSignalSpy lockSpy(session, &Lingmo::ShellSession::sessionLocked);
    QVERIFY(lockSpy.isValid());

    session->Lock();
    QCOMPARE(lockSpy.count(), 1);
}

void tst_ShellSession::logoutSignal()
{
    auto *session = Lingmo::ShellSession::instance();
    QSignalSpy logoutSpy(session, &Lingmo::ShellSession::logoutRequested);
    QVERIFY(logoutSpy.isValid());

    session->Logout();
    QCOMPARE(logoutSpy.count(), 1);
}

void tst_ShellSession::shutdownSignal()
{
    auto *session = Lingmo::ShellSession::instance();
    QSignalSpy shutdownSpy(session, &Lingmo::ShellSession::shutdownRequested);
    QVERIFY(shutdownSpy.isValid());

    session->Shutdown();
    QCOMPARE(shutdownSpy.count(), 1);
}

void tst_ShellSession::rebootSignal()
{
    auto *session = Lingmo::ShellSession::instance();
    QSignalSpy rebootSpy(session, &Lingmo::ShellSession::rebootRequested);
    QVERIFY(rebootSpy.isValid());

    session->Reboot();
    QCOMPARE(rebootSpy.count(), 1);
}

QTEST_MAIN(tst_ShellSession)
#include "tst_ShellSession.moc"
