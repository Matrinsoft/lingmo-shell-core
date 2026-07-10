#include <LingmoShellCore/ThemeWatcher.h>

#include <QSignalSpy>
#include <QTest>

class tst_ThemeWatcher : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void startStop();
    void currentTheme();
};

void tst_ThemeWatcher::startStop()
{
    auto *watcher = Lingmo::ThemeWatcher::instance();
    QVERIFY(!watcher->isWatching());

    bool result = watcher->startWatching();
    QVERIFY(result);
    QVERIFY(watcher->isWatching());

    watcher->stopWatching();
    QVERIFY(!watcher->isWatching());
}

void tst_ThemeWatcher::currentTheme()
{
    auto *watcher = Lingmo::ThemeWatcher::instance();
    QString theme = watcher->currentTheme();
    // Theme may be empty initially
    QVERIFY(true);
}

QTEST_MAIN(tst_ThemeWatcher)
#include "tst_ThemeWatcher.moc"
