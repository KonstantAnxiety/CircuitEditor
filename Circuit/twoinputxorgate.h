#ifndef TWOINPUTXORGATE_H
#define TWOINPUTXORGATE_H

#include <twoinputgate.h>

class TwoInputXorGate: public TwoInputGate
{
public:
    TwoInputXorGate();
    TwoInputXorGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputXorGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 10; };

    virtual void write(std::ostream& out) const override{
        out << "10 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const TwoInputXorGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTXORGATE_H
