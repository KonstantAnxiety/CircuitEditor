#include "twoinputnandgate.h"

#include <QGraphicsItem>

TwoInputNandGate::TwoInputNandGate()
{

}

void TwoInputNandGate::draw(QGraphicsScene *scene)
{
    TwoInputGate::draw(scene);
    QPainterPath p;
    p.moveTo(ex()-w()/7*5, ey()-h()/8*3);
    p.arcTo(ex()-w()/7*8, ey()-h()/8*3, w()/7*6, h()/4*3, -90, 180);
    p.addEllipse(ex()-w()/7*2, ey()-8, 16, 16);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    p = QPainterPath(t.map(p));
    scene->addPath(p, QPen(Qt::black, 5), QBrush(Qt::white))->setZValue(6);
}
