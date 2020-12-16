#ifndef TWOINPUTNANDGATE_H
#define TWOINPUTNANDGATE_H

#include <twoinputgate.h>

class TwoInputNandGate: public TwoInputGate
{
public:
    TwoInputNandGate();
    TwoInputNandGate(double ex, double ey, double r=0, double w=175, double h=100)
        : TwoInputGate(ex, ey, r, w, h) { };
    ~TwoInputNandGate() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 6; };

    virtual void write(std::ostream& out) const override{
        out << "6 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h();
    }

    friend std::ostream& operator<<(std::ostream& out, const TwoInputNandGate &c)
    {
        c.write(out);
        return out;
    }
};

#endif // TWOINPUTNANDGATE_H
