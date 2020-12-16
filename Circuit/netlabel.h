#ifndef NETLABEL_H
#define NETLABEL_H

#include <endcomponent.h>

class NetLabel: public EndComponent
{
public:
    NetLabel();
    NetLabel(double ex, double ey, double r=0, double w=150, double h=100)
        : EndComponent(ex, ey, r, w, h) { };
    ~NetLabel() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 4; };

    virtual void write(std::ostream& out) const override{
        out << "4 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h() << " " << getText().toStdString();
    }

    friend std::ostream& operator<<(std::ostream& out, const NetLabel &c)
    {
        c.write(out);
        return out;
    }
};

#endif // NETLABEL_H
