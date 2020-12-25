#ifndef TWOINPUTNORGATE_H
#define TWOINPUTNORGATE_H

#include <twoinputgate.h>

class TwoInputNorGate: public TwoInputGate
{
public:
    TwoInputNorGate(): TwoInputGate() { };
    TwoInputNorGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputNorGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 8; };

    friend std::ostream& operator<<(std::ostream& out, const TwoInputNorGate &c) {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTNORGATE_H
