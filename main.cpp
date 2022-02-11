// Author: Remy van Elst, https://raymii.org. License: GNU AGPLv3

#include "SaveToDisk.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDirIterator>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    app.setOrganizationName("Raymii.org");
    app.setOrganizationDomain("raymii.org");
    app.setApplicationName("SaveToDiskExample");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    SaveToDisk* saveExample = new SaveToDisk();
    qmlRegisterSingletonInstance<SaveToDisk>("org.raymii.SaveToDisk", 1, 0, "SaveToDisk", saveExample);

    engine.load(url);

    qDebug() << "Start of list of all resources in the qrc file:";
    QDirIterator it(":/", QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();
    qDebug() << "End of list of all resources in the qrc file:";

    return app.exec();
}
