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
    virtual int id() const override { return 13; };

    virtual void write(std::ostream& out) const override{
        out << "13 " << ex() << " " << ey() << " "
            << r() << " " <<  w() << " " << h() << " " << getText().toStdString();
    }

    /*virtual void writeBinary(std::ostream& out) const override {
        char c = 'L';
        out.write((char*)&c, sizeof(char));
        double t;
        t = ex(); out.write((char*)&t, sizeof(double));
        t = ey(); out.write((char*)&t, sizeof(double));
        t = r(); out.write((char*)&t, sizeof(double));
        t = w(); out.write((char*)&t, sizeof(double));
        t = h(); out.write((char*)&t, sizeof(double));
        QString s = getText();
        //out.write((char*)&s, sizeof(QString));
    }*/

    friend std::ostream& operator<<(std::ostream& out, const LogicBlock &c)
    {
        c.write(out);
        return out;
    }
};

#endif // LOGICBLOCK_H
