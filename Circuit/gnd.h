#ifndef GND_H
#define GND_H

#include <endcomponent.h>

class GND: public EndComponent
{
public:
    GND() { setW(50); setH(50); };
    GND(double ex, double ey, double r=0, double w=50, double h=50)
        : EndComponent(ex, ey, r, w, h) { };
    ~GND() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 3; };

    friend std::ostream& operator<<(std::ostream& out, const GND &c) {
        c.write(out);
        return out;
    }
};

#endif // GND_H
