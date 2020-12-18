#ifndef RESISTOR_H
#define RESISTOR_H

#include <serialcomponent.h>

class Resistor: public SerialComponent
{
public:
    Resistor(): SerialComponent() { setW(150); setH(50); };
    Resistor(double ex, double ey, double r=0, double w=150, double h=100)
        : SerialComponent(ex, ey, r, w, h) { };
    ~Resistor() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 11; };

    friend std::ostream& operator<<(std::ostream& out, const Resistor &c)
    {
        c.write(out);
        return out;
    }
};

#endif // RESISTOR_H
