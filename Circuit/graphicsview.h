#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>
#include "component.h"
#include "twoinputgate.h"
#include "twoinputandgate.h"
#include "twoinputnandgate.h"
#include "resistor.h"
#include "gnd.h"
#include "netlabel.h"
#include "logicblock.h"
#include "twoinputorgate.h"
#include "twoinputnorgate.h"
#include "twoinputxorgate.h"
#include "notgate.h"
#include "capacitor.h"
#include "textdialog.h"
#include "vector.h"
#include "vector.cpp"

typedef std::shared_ptr<Component> pComponent;

class GraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent);
    ~GraphicsView();
    const QString &getPath() const { return path; };
    bool isSaved() const { return saved; };
    void createNewChart();
    void save();
    void saveToSvg(const QString &path);
    void saveToImage(const QString &path);
    void saveAsBinary(const QString &path);
    void saveAsTxt(const QString &path);
    void openBinary(const QString &path);
    void openTxt(const QString &path);
    void addNode(int id);
    void addGrid();
    void removeGrid();
    void rotate();

signals:
    void savedStateChanged();

private slots:
    void slotAlarmTimer();

private:
    QTimer *timer;
    QGraphicsScene *scene;
    Vector<pComponent> components;
    QGraphicsItemGroup *grid;
    QGraphicsItemGroup *wires;
    QGraphicsItemGroup *connections;
    int nodeToAdd, nowMoving, lineDir;
    int panStartX, panStartY;
    bool pan, line, saved;
    QString path;
    QPoint lastPoint;
    pComponent tmp;

    pComponent defaultComponentFactory(int id);
    pComponent componentFactory(int id, double x=0, double y=0,
                                double r=0, double w=0, double h=0);
    int hoveredNode(QMouseEvent *event) const;
    void snapToGrid(QPointF *pt, double step = 25) const;

    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GRAPHICSVIEW_H
