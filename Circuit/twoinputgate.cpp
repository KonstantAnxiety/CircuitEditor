#include "twoinputgate.h"

#include <QGraphicsItem>

void TwoInputGate::draw(QGraphicsScene *scene)
{
    QLineF input1 = QLineF(ex()-w(), ey()-h()/4, ex()-w()/7*4, ey()-h()/4);
    QLineF input2 = QLineF(ex()-w(), ey()+h()/4, ex()-w()/7*4, ey()+h()/4);
    QLineF output = QLineF(ex()-w()/7*2, ey(), ex(), ey());
    QTransform t;
    t.translate(ex(), ey());
    t.rotate(r());
    t.translate(-ex(), -ey());
    input1 = t.map(input1);
    input2 = t.map(input2);
    output = t.map(output);
    if (hovered()){
        QVector<QPoint> points;
        points.push_back(QPoint(ex()-w(), ey()-h()/2));
        points.push_back(QPoint(ex()-w(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()-h()/2));
        QPolygonF border = QPolygonF(points);
        border = t.map(border);
        scene->addPolygon(border, QPen(Qt::blue, 4, Qt::DotLine))->setZValue(15);
    }
    scene->addLine(input1, QPen(Qt::black, 5))->setZValue(5);
    scene->addLine(input2, QPen(Qt::black, 5))->setZValue(5);
    scene->addLine(output, QPen(Qt::black, 5))->setZValue(5);
}
