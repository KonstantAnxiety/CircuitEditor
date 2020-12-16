#include "notgate.h"

#include <QGraphicsItem>

NotGate::NotGate()
{

}

void NotGate::draw(QGraphicsScene *scene)
{
    SerialComponent::draw(scene);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    QPainterPath p;
    p.moveTo(ex()-w()/6*2, ey());
    p.lineTo(ex()-w()/6*4, ey()-h()/4);
    p.lineTo(ex()-w()/6*4, ey()+h()/4);
    p.lineTo(ex()-w()/6*2, ey());
    p.addEllipse(ex()-w()/6*2, ey()-8, 16, 16);
    p = QPainterPath(t.map(p));
    scene->addPath(p, QPen(Qt::black, 3), QBrush(Qt::white))->setZValue(6);
}
