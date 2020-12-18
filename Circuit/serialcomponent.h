#ifndef SERIALCOMPONENT_H
#define SERIALCOMPONENT_H

#include "component.h"

class SerialComponent: public Component
{
public:
    SerialComponent(): Component() { };
    SerialComponent(double ex, double ey, double r=0, double w=150, double h=50)
        : Component(ex, ey, r, w, h) { };
    ~SerialComponent() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 0; };

    friend std::ostream& operator<<(std::ostream& out, const SerialComponent &c)
    {
        c.write(out);
        return out;
    }
};

#endif // SERIALCOMPONENT_H
