#include "serialcomponent.h"

#include <QGraphicsItem>

SerialComponent::SerialComponent()
{

}

void SerialComponent::draw(QGraphicsScene *scene)
{
    QLineF input = QLineF(ex()-w(), ey(), ex()-w()/6*4, ey());
    QLineF output = QLineF(ex()-w()/6*2, ey(), ex(), ey());
    QTransform t;
    t.translate(ex(), ey());
    t.rotate(r());
    t.translate(-ex(), -ey());
    input = t.map(input);
    output = t.map(output);
    if (hovered()){
        QVector<QPoint> points;
        points.push_back(QPoint(ex()-w(), ey()-h()/2));
        points.push_back(QPoint(ex()-w(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()-h()/2));
        QPolygonF border = QPolygonF(points);
        border = t.map(border);
        scene->addPolygon(border, QPen(Qt::blue, 4, Qt::DotLine))->setZValue(5);
    }
    scene->addLine(input, QPen(Qt::black, 5))->setZValue(5);
    scene->addLine(output, QPen(Qt::black, 5))->setZValue(5);
}
