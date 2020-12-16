#include "gnd.h"

#include <QGraphicsItem>

GND::GND()
{

}

void GND::draw(QGraphicsScene *scene)
{
    EndComponent::draw(scene);
    QLineF line1 = QLineF(ex()+25, ey()-20, ex()+25, ey()+20);
    QLineF line2 = QLineF(ex()+25+25/2, ey()-14, ex()+25+25/2, ey()+14);
    QLineF line3 = QLineF(ex()+25+25, ey()-8, ex()+25+25, ey()+8);
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    line1 = QLineF(t.map(line1));
    line2 = QLineF(t.map(line2));
    line3 = QLineF(t.map(line3));
    scene->addLine(line1, QPen(Qt::black, 5))->setZValue(6);
    scene->addLine(line2, QPen(Qt::black, 5))->setZValue(6);
    scene->addLine(line3, QPen(Qt::black, 5))->setZValue(6);
}
