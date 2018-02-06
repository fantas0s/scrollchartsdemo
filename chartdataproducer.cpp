#include "chartdataproducer.h"
#include <QDebug>

ChartDataProducer* ChartDataProducer::m_instance = Q_NULLPTR;

ChartDataProducer::ChartDataProducer() :
    m_filledData(0),
    m_lineData(0),
    m_xMaximum(100)
{
    startTimer(10);
}

QObject* ChartDataProducer::chartDataProducerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if (!m_instance) {
        m_instance = new ChartDataProducer();
    }
    return m_instance;
}

void ChartDataProducer::setXMaximum(int newMax)
{
    if (newMax > 100) {
        m_xMaximum = newMax;
        emit xMaximumChanged(m_xMaximum);
    }
}

int ChartDataProducer::getXMaximum()
{
    return m_xMaximum;
}

void ChartDataProducer::setFilledDataSeries(QAbstractSeries *series)
{
    m_filledData = qobject_cast<QAreaSeries*>(series);
}

void ChartDataProducer::setLineDataSeries(QAbstractSeries *series)
{
    m_lineData = qobject_cast<QLineSeries*>(series);
}

void ChartDataProducer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (m_lineData) {
        m_lineVector.append(QPointF(m_xMaximum, 40+(qrand()%20)));
        for(QVector<QPointF>::iterator it = m_lineVector.begin(); it != m_lineVector.end(); ++it) {
            it->setX(it->x()-1);
        }
        if (m_lineVector.length() > m_xMaximum)
            m_lineVector.removeFirst();
        m_lineData->replace(m_lineVector);
    }
    if (m_filledData) {
        m_filledVector.append(QPointF(m_xMaximum, 65+(qrand()%35)));
        for(QVector<QPointF>::iterator it = m_filledVector.begin(); it != m_filledVector.end(); ++it) {
            it->setX(it->x()-1);
        }
        if (m_filledVector.length() > m_xMaximum)
            m_filledVector.removeFirst();
        m_filledData->upperSeries()->replace(m_filledVector);
    }
    static int expireTimes = 0;
    expireTimes++;
    if (expireTimes > 100) {
        expireTimes = 0;
        qDebug() << QTime::currentTime().toString("mm:ss.zzz");
    }
}
