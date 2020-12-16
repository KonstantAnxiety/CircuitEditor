#include "logicblock.h"

#include <QGraphicsItem>

LogicBlock::LogicBlock()
{

}

void LogicBlock::draw(QGraphicsScene *scene)
{
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    QVector<QPoint> points;
    points.push_back(QPoint(ex()-w(), ey()-h()/2));
    points.push_back(QPoint(ex()-w(), ey()+h()/2));
    points.push_back(QPoint(ex(), ey()+h()/2));
    points.push_back(QPoint(ex(), ey()-h()/2));
    QPolygonF box = QPolygonF(points);
    box = t.map(box);
    if (hovered())
        scene->addPolygon(box, QPen(Qt::blue, 2, Qt::DotLine))->setZValue(15);
    scene->addPolygon(box, QPen(Qt::black, 3), QBrush(Qt::white))->setZValue(4);

    QGraphicsTextItem *io = new QGraphicsTextItem;
    io->setFont(QFont("Courier New", 16, -1, 1));
    io->setPlainText(getText());
    QPointF c = QPointF(ex() - w()/2,
                        ey());
    c = t.map(c);
    c.setX(c.x() - io->boundingRect().width()*.5);
    c.setY(c.y() - io->boundingRect().height()*.5);
    io->setPos(c);
    io->setZValue(14);
    scene->addItem(io);
}
