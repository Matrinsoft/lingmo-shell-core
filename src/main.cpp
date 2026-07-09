#include <LingmoShellCore/ShellRuntime.h>
#include <LingmoShellCore/SurfaceManager.h>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("lingmo-shell-core"));
    QCoreApplication::setApplicationVersion(QStringLiteral("1.0.0"));

    qInfo("lingmo-shell-core: starting...");

    auto *runtime = Lingmo::ShellRuntime::instance();
    if (!runtime->initialize()) {
        qCritical("lingmo-shell-core: failed to initialize runtime");
        return 1;
    }

    qInfo("lingmo-shell-core: running");

    int result = app.exec();

    runtime->shutdown();
    qInfo("lingmo-shell-core: exited with code %d", result);

    return result;
}
