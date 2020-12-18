#include "capacitor.h"

#include <QGraphicsItem>

void Capacitor::draw(QGraphicsScene *scene)
{
    SerialComponent::draw(scene);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    QLineF line1(ex()-w()/6*4, ey()-h()/2, ex()-w()/6*4, ey()+h()/2);
    QLineF line2(ex()-w()/6*2, ey()-h()/2, ex()-w()/6*2, ey()+h()/2);
    line1 = t.map(line1);
    line2 = t.map(line2);
    scene->addLine(line1, QPen(Qt::black, 5))->setZValue(6);
    scene->addLine(line2, QPen(Qt::black, 5))->setZValue(6);
}
