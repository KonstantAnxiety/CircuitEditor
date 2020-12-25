#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

#include "component.h"

class LogicBlock: public Component
{
public:
    LogicBlock(): Component() { };
    LogicBlock(double ex, double ey, double r=0, double w=50, double h=50)
        : Component(ex, ey, r, w, h) { };
    ~LogicBlock() = default;
    virtual void draw(QGraphicsScene *scene) override;
    virtual int id() const override { return 13; };

    friend std::ostream& operator<<(std::ostream& out, const LogicBlock &c) {
        c.write(out);
        return out;
    }
};

#endif // LOGICBLOCK_H
