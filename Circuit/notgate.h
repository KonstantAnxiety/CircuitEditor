#ifndef NOTGATE_H
#define NOTGATE_H

#include <serialcomponent.h>

class NotGate: public SerialComponent
{
public:
    NotGate(): SerialComponent() { setW(150); setH(100); };
    NotGate(double ex, double ey, double r=0, double w=150, double h=100)
        : SerialComponent(ex, ey, r, w, h) { };
    ~NotGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 9; };

    friend std::ostream& operator<<(std::ostream& out, const NotGate &c) {
        c.write(out);
        return out;
    }
};

#endif // NOTGATE_H
