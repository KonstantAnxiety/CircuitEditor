#ifndef NETLABEL_H
#define NETLABEL_H

#include <endcomponent.h>

class NetLabel: public EndComponent
{
public:
    NetLabel() { setW(100); setH(50); };
    NetLabel(double ex, double ey, double r=0, double w=100, double h=50)
        : EndComponent(ex, ey, r, w, h) { };
    ~NetLabel() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 4; };

    friend std::ostream& operator<<(std::ostream& out, const NetLabel &c) {
        c.write(out);
        return out;
    }
};

#endif // NETLABEL_H
