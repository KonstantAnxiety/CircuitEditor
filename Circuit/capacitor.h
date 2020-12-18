#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <serialcomponent.h>

class Capacitor: public SerialComponent
{
public:
    Capacitor(): SerialComponent() { setW(150); setH(50); };
    Capacitor(double ex, double ey, double r=0, double w=150, double h=50)
        : SerialComponent(ex, ey, r, w, h) { };
    ~Capacitor() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 12; };

    friend std::ostream& operator<<(std::ostream& out, const Capacitor &c)
    {
        c.write(out);
        return out;
    }
};

#endif // CAPACITOR_H
