#ifndef TWOINPUTNORGATE_H
#define TWOINPUTNORGATE_H

#include <twoinputgate.h>

class TwoInputNorGate: public TwoInputGate
{
public:
    TwoInputNorGate();
    TwoInputNorGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputNorGate() = default;
    virtual void draw(QGraphicsScene *scene) override;

    virtual void write(std::ostream& out) const override{
        out << "8 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const TwoInputNorGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTNORGATE_H
