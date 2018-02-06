#include <QApplication>
#include <QQmlApplicationEngine>
#include "chartdataproducer.h"

int main(int argc, char *argv[])
{
    // QtChars mandate using QApplication as it uses the graphics view fw
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<ChartDataProducer>("ChartDataProducer", 1, 0, "ChartDataProducer", ChartDataProducer::chartDataProducerProvider);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
