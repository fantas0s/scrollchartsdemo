import QtQuick 2.8
import QtQuick.Window 2.2
import QtCharts 2.1
import ChartDataProducer 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "white"

    ChartView {
        id: scrollChart
        anchors.fill: parent
        backgroundColor: "white"
        legend.visible: false

        // Hide the value axis labels; labels are drawn separately.
        ValueAxis {
            id: valueAxisX

            min: 0
            max: ChartDataProducer.xMaximum
            visible: true
        }

        ValueAxis {
            id: valueAxisY

            min: 0
            max: 110
            visible: true
        }

        AreaSeries {
            id: areaDataSeries
            upperSeries: LineSeries {
                XYPoint { x: 98; y: 1 }
                XYPoint { x: 99; y: 1 }
            }
            axisX: valueAxisX
            axisY: valueAxisY
            color: "black"
            useOpenGL: true
        }

        LineSeries {
            id: lineDataSeries

            axisX: valueAxisX
            axisY: valueAxisY
            color: "red"
            width: 1
            useOpenGL: true
        }
        Component.onCompleted: {
            ChartDataProducer.setLineDataSeries(lineDataSeries)
            ChartDataProducer.setFilledDataSeries(areaDataSeries)
        }
        onPlotAreaChanged: ChartDataProducer.xMaximum = plotArea.width;
    }
}
