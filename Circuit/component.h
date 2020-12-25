#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsScene>
#include <QDebug>

class Component
{
public:
    Component();
    Component(double ex, double ey, double r=0, double w=0, double h=0, QString s="NONE")
        : m_ex{ex}, m_ey{ey}, m_r{r}, m_w{w}, m_h{h}, m_text(s) { };
    ~Component() = default;
    double ex() const { return m_ex; };
    double ey() const { return m_ey; };
    double w() const { return m_w; };
    double h() const { return m_h; };
    double r() const { return m_r; };
    const QString &getText() const { return m_text; };
    bool hovered() const { return m_hover; };

    void setHover(bool hov = false) { m_hover = hov; };
    void rotate() { m_r += 90; };
    void setRotation(double r) { m_r = r; };
    void setPos(double ex, double ey) { m_ex = ex; m_ey = ey; };
    void setW(double w) { m_w = w; };
    void setH(double h) { m_h = h; };
    void setText(const QString &text) { m_text = text; };

    virtual void draw(QGraphicsScene *scene) = 0;
    virtual int id() const { return 0; };
    virtual bool hover(double x, double y) const;
    void write(std::ostream& out) const;
    void writeBinary(std::ostream& out) const;
    void readBinary(std::istream& out);

private:
    double m_ex{0.0}, m_ey{0.0},
           m_r{0.0},
           m_w{0.0}, m_h{0.0};
           bool m_hover{0};
    QString m_text{"NONE"};
};

#endif // COMPONENT_H
