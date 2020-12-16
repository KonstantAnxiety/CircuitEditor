#include "twoinputandgate.h"

#include <QGraphicsItem>

TwoInputAndGate::TwoInputAndGate()
{

}

void TwoInputAndGate::draw(QGraphicsScene *scene)
{
    TwoInputGate::draw(scene);
    QPainterPath p;
    p.moveTo(ex()-w()/7*5, ey()-h()/8*3);
    p.arcTo(ex()-w()/7*8, ey()-h()/8*3, w()/7*6, h()/4*3, -90, 180);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    p = QPainterPath(t.map(p));
    scene->addPath(p, QPen(Qt::black, 3), QBrush(Qt::white))->setZValue(6);
}