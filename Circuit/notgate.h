#ifndef NOTGATE_H
#define NOTGATE_H

#include <serialcomponent.h>

class NotGate: public SerialComponent
{
public:
    NotGate();
    NotGate(double ex, double ey, double r=0, double w=150, double h=100)
        : SerialComponent(ex, ey, r, w, h) { };
    ~NotGate() = default;
    virtual void draw(QGraphicsScene *scene) override;

    virtual void write(std::ostream& out) const override{
        out << "9 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const NotGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // NOTGATE_H
