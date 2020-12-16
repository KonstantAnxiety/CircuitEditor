#ifndef GND_H
#define GND_H

#include <endcomponent.h>

class GND: public EndComponent
{
public:
    GND();
    GND(double ex, double ey, double r=0, double w=150, double h=100)
        : EndComponent(ex, ey, r, w, h) { };
    ~GND() = default;
    virtual void draw(QGraphicsScene *scene) override;

    virtual void write(std::ostream& out) const override{
        out << "3 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const GND &c)
    {
        c.write(out);
        return out;
    }
};

#endif // GND_H
