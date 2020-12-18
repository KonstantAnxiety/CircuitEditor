#ifndef TWOINPUTORGATE_H
#define TWOINPUTORGATE_H

#include <twoinputgate.h>

class TwoInputOrGate: public TwoInputGate
{
public:
    TwoInputOrGate(): TwoInputGate() { };
    TwoInputOrGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputOrGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 7; };

    friend std::ostream& operator<<(std::ostream& out, const TwoInputOrGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTORGATE_H
