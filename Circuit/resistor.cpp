#include "resistor.h"

#include <QGraphicsItem>

void Resistor::draw(QGraphicsScene *scene)
{
    SerialComponent::draw(scene);
    QPainterPath p;
    double amp = 22;
    int dir = 1;
    double freq = 11;
    double lambda = w()/2 / freq;
    p.moveTo(QPointF(ex()-w()/6*4, ey()));
    for (double x = ex()-w()/6*4+lambda; x <= ex()-w()/6*2-lambda; x += lambda) {
        p.lineTo(QPointF(x, ey()+amp*dir));
        dir *= -1;
    }
    p.lineTo(QPointF(ex()-w()/6*2, ey()));

    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    p = QPainterPath(t.map(p));
    scene->addPath(p, QPen(Qt::black, 5))->setZValue(6);
}
