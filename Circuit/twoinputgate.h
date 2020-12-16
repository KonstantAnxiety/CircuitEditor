#ifndef TWOINPUTGATE_H
#define TWOINPUTGATE_H

#include "component.h"

class TwoInputGate: public Component
{
public:
    TwoInputGate();
    TwoInputGate(double ex, double ey, double r=0, double w=175, double h=100)
        : Component(ex, ey, r, w, h) { };
    ~TwoInputGate() = default;
    virtual void draw(QGraphicsScene *scene) override;

    virtual void write(std::ostream& out) const override{
        out << "G " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const TwoInputGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTGATE_H
