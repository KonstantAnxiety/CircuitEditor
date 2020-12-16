#ifndef TWOINPUTANDGATE_H
#define TWOINPUTANDGATE_H

#include <twoinputgate.h>

class TwoInputAndGate: public TwoInputGate
{
public:
    TwoInputAndGate();
    TwoInputAndGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputAndGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 5; };

    virtual void write(std::ostream& out) const override{
        out << "5 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const TwoInputAndGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTANDGATE_H
