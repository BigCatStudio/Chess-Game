#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "headers/chessboardutilities.h"
#include "headers/tilesfigureshandler.h"
#include "headers/tileback.h"
#include "headers/figureback.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // It has to be declared here because engine will try to get to property that is already destroyed
    // https://forum.qt.io/topic/130531/cannot-read-property-sendsignalwitharg-of-null/3
    ChessBoardUtilities chessBoardUtilities;
    TilesFiguresHandler tilesFiguresHandler;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("chessBoardUtilities", &chessBoardUtilities);
    engine.rootContext()->setContextProperty("tilesFiguresHandler", &tilesFiguresHandler);

    qmlRegisterType<TileBack>("Cpp.Classes", 1.0, 0.0, "TileBack");
    qmlRegisterType<FigureBack>("Cpp.Classes", 1.0, 0.0, "FigureBack");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
