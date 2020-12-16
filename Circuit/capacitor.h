#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <serialcomponent.h>

class Capacitor: public SerialComponent
{
public:
    Capacitor();
    Capacitor(double ex, double ey, double r=0, double w=150, double h=100)
        : SerialComponent(ex, ey, r, w, h) { };
    ~Capacitor() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 12; };

    virtual void write(std::ostream& out) const override{
        out << "12 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const Capacitor &c)
    {
        c.write(out);
        return out;
    }
};

#endif // CAPACITOR_H
