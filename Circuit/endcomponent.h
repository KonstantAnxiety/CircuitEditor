#ifndef ENDCOMPONENT_H
#define ENDCOMPONENT_H

#include "component.h"

class EndComponent: public Component
{
public:
    EndComponent(): Component() { };
    EndComponent(double ex, double ey, double r=0, double w=50, double h=50)
        : Component(ex, ey, r, w, h) { };
    ~EndComponent() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 0; };
    virtual bool hover(double x, double y) const override;

    friend std::ostream& operator<<(std::ostream& out, const EndComponent &c)
    {
        c.write(out);
        return out;
    }
};

#endif // ENDCOMPONENT_H
