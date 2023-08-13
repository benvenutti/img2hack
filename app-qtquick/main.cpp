#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );
    QQmlApplicationEngine engine;
    const QUrl            url( u"qrc:/example/main.qml"_qs );
    engine.load( url );

    return app.exec();
}
