#include "twoinputxorgate.h"

#include <QGraphicsItem>

TwoInputXorGate::TwoInputXorGate()
{

}

void TwoInputXorGate::draw(QGraphicsScene *scene)
{
    TwoInputGate::draw(scene);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    QPainterPath p;
    p.moveTo(ex()-w()/7*5, ey()+h()/8*3);
    p.arcTo(ex()-w()/7*8, ey()-h()/8*3, w()/7*6, h()/4*3, -90, 180);
    p.moveTo(ex()-w()/7*5, ey()+h()/8*3);
    p.arcTo(ex()-w()/14*11, ey()-h()/8*3, w()/14*2, h()/4*3, -90, 180);
    p = t.map(p);
    scene->addPath(p, QPen(Qt::black, 5), QBrush(Qt::white))->setZValue(6);

    p.clear();
    p.moveTo(ex()-w()/7*5-10, ey()+h()/8*3);
    p.arcTo(ex()-w()/14*11-10, ey()-h()/8*3, w()/14*2, h()/4*3, -90, 180);
    p = t.map(p);
    scene->addPath(p, QPen(Qt::black, 5), QBrush(Qt::transparent))->setZValue(6);
}
