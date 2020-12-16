#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsScene>

class Component
{
public:
    Component();
    Component(double ex, double ey, double r=0, double w=0, double h=0)
        : m_ex{ex}, m_ey{ey}, m_r{r}, m_w{w}, m_h{h} { };
    ~Component() = default;
    double ex() const { return m_ex; };
    double ey() const { return m_ey; };
    double w() const { return m_w; };
    double h() const { return m_h; };
    double r() const { return m_r; };
    bool hovered() const { return m_hover; };
    virtual void setHover(bool hov = false) { m_hover = hov; };
    virtual void rotate() { m_r += 90; };
    virtual void setRotation(double r) { m_r = r; };
    virtual void setPos(double ex, double ey) { m_ex = ex; m_ey = ey; };
    virtual void setW(double w) { m_w = w; };
    virtual void setH(double h) { m_h = h; };
    virtual void draw(QGraphicsScene *scene) = 0;
    virtual void setText(const QString &text) { m_text = text; };
    virtual const QString &getText() const { return m_text; };
    virtual bool hover(double x, double y) const { // ROTATION
        QTransform t;
        t.translate(ex(), ey());
        t.rotate(r());
        t.translate(-ex(), -ey());
        QVector<QPoint> points;
        points.push_back(QPoint(ex()-w(), ey()-h()/2));
        points.push_back(QPoint(ex()-w(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()+h()/2));
        points.push_back(QPoint(ex(), ey()-h()/2));
        QPolygonF border = QPolygonF(points);
        border = t.map(border);
        return (border.containsPoint(QPointF(x, y), Qt::OddEvenFill));
    }

    virtual void write(std::ostream& out) const {
        out << "C " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

private:
    double m_ex{0.0}, m_ey{0.0},
           m_r{0.0},
           m_w{0.0}, m_h{0.0};
    bool m_hover;
    QString m_text;
};

#endif // COMPONENT_H
