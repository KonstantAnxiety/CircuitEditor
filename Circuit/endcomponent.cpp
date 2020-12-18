#include "endcomponent.h"

#include <QGraphicsItem>

void EndComponent::draw(QGraphicsScene *scene)
{
    QLineF input = QLineF(ex(), ey(), ex()+25, ey());
    QTransform t;
    t.translate(ex(), ey());
    t.rotate(r());
    t.translate(-ex(), -ey());
    input = t.map(input);
    if (hovered()){
        QVector<QPoint> points;
        points.push_back(QPoint(ex(), ey()-h()/2));
        points.push_back(QPoint(ex(), ey()+h()/2));
        points.push_back(QPoint(ex()+w(), ey()+h()/2));
        points.push_back(QPoint(ex()+w(), ey()-h()/2));
        QPolygonF border = QPolygonF(points);
        border = t.map(border);
        scene->addPolygon(border, QPen(Qt::blue, 4, Qt::DotLine))->setZValue(15);
    }
    scene->addLine(input, QPen(Qt::black, 5))->setZValue(5);
}

bool EndComponent::hover(double x, double y) const{
    QTransform t;
    t.translate(ex(), ey()); t.rotate(r()); t.translate(-ex(), -ey());
    QVector<QPoint> points;
    points.push_back(QPoint(ex(), ey()-h()/2));
    points.push_back(QPoint(ex(), ey()+h()/2));
    points.push_back(QPoint(ex()+w(), ey()+h()/2));
    points.push_back(QPoint(ex()+w(), ey()-h()/2));
    QPolygonF border = QPolygonF(points);
    border = t.map(border);
    return (border.containsPoint(QPointF(x, y), Qt::OddEvenFill));
}
