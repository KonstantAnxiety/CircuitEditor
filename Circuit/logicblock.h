#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

#include "component.h"

class LogicBlock: public Component
{
public:
    LogicBlock();
    LogicBlock(double ex, double ey, double r=0, double w=50, double h=50)
        : Component(ex, ey, r, w, h) { };
    ~LogicBlock() = default;
    virtual void draw(QGraphicsScene *scene) override;

    virtual void write(std::ostream& out) const override{
        out << "13 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h() << " " << getText().toStdString();
    }

    friend std::ostream& operator<<(std::ostream& out, const LogicBlock &c)
    {
        c.write(out);
        return out;
    }
};

#endif // LOGICBLOCK_H
