#ifndef ENDCOMPONENT_H
#define ENDCOMPONENT_H

#include "component.h"

class EndComponent: public Component
{
public:
    EndComponent();
    EndComponent(double ex, double ey, double r=0, double w=50, double h=50)
        : Component(ex, ey, r, w, h) { };
    ~EndComponent() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 0; };
    virtual bool hover(double x, double y) const override{
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

    virtual void write(std::ostream& out) const override{
        out << "E " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const EndComponent &c)
    {
        c.write(out);
        return out;
    }
};

#endif // ENDCOMPONENT_H
