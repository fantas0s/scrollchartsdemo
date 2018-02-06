#ifndef CHARTDATAPRODUCER_H
#define CHARTDATAPRODUCER_H
#include <QObject>
#include <QtCharts/QtCharts>
#include <QVector>
#include <QPointF>

class QQmlEngine;
class QJSEngine;

class ChartDataProducer : public QObject
{
    Q_OBJECT
public:
    static QObject* chartDataProducerProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    Q_INVOKABLE void setFilledDataSeries(QAbstractSeries *series);
    Q_INVOKABLE void setLineDataSeries(QAbstractSeries *series);
    void setXMaximum(int newMax);
    int getXMaximum();
    Q_PROPERTY(int xMaximum READ getXMaximum WRITE setXMaximum NOTIFY xMaximumChanged)
signals:
    void xMaximumChanged(int newMax);
private slots:
    void timerEvent(QTimerEvent *event);
private:
    ChartDataProducer();
    static ChartDataProducer* m_instance;
    QAreaSeries *m_filledData;
    QLineSeries *m_lineData;
    QVector<QPointF> m_filledVector;
    QVector<QPointF> m_lineVector;
    int m_xMaximum;
};
#endif // CHARTDATAPRODUCER_H
