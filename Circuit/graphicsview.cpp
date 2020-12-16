#include <QScrollBar>
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include "graphicsview.h"
#include <QDebug>
#include <QTimer>
#include <QFont>
#include <QDialog>
#include <math.h>
#include <fstream>

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);
    this->setMinimumHeight(100);
    this->setMinimumWidth(300);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 3000, 3000);
    this->setScene(scene);

    nodeToAdd = 0;
    nowMoving = -1;
    _pan = false;
    _line = false;
    saved = true;

    grid = new QGraphicsItemGroup();
    addGrid();
    grid->setZValue(1);
    scene->addItem(grid);

    wires = new QGraphicsItemGroup;
    wires->setZValue(2);
    scene->addItem(wires);

    connections = new QGraphicsItemGroup;
    connections->setZValue(2);
    scene->addItem(connections);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(20);
}

GraphicsView::~GraphicsView()
{
    delete timer;
    foreach(QGraphicsItem *item, scene->items()) { delete item; }
    delete scene;
}

void GraphicsView::createNewChart()
{
    components.clear();
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->group() == connections || item->group() == wires) {
            delete item;
        }
    }
    path = "";
    saved = true;
    emit savedStateChanged();
}

void GraphicsView::addNode(int id)
{
    nodeToAdd = id;
    if (nodeToAdd > 2 && nodeToAdd < 13) {
        tmp.reset();
        switch (nodeToAdd) {
        case 3:
            tmp = std::shared_ptr<Component>(new GND(0, 0, 0, 50, 50));
            break;
        case 4:
            tmp = std::shared_ptr<Component>(new NetLabel(0, 0, 0, 100, 50));
            break;
        case 5:
            tmp = std::shared_ptr<Component>(new TwoInputAndGate(0, 0, 0));
            break;
        case 6:
            tmp = std::shared_ptr<Component>(new TwoInputNandGate(0, 0, 0));
            break;
        case 7:
            tmp = std::shared_ptr<Component>(new TwoInputOrGate(0, 0, 0));
            break;
        case 8:
            tmp = std::shared_ptr<Component>(new TwoInputNorGate(0, 0, 0));
            break;
        case 9:
            tmp = std::shared_ptr<Component>(new NotGate(0, 0, 0));
            break;
        case 10:
            tmp = std::shared_ptr<Component>(new TwoInputXorGate(0, 0, 0));
            break;
        case 11:
            tmp = std::shared_ptr<Component>(new Resistor(0, 0, 0, 150, 50));
            break;
        case 12:
            tmp = std::shared_ptr<Component>(new Capacitor(0, 0, 0, 150, 50));
            break;
        }
    }
}

void GraphicsView::save()
{
    if (!path.isEmpty()) {
        saveAs(path);
        saved = true;
        emit savedStateChanged();
    }
}

void GraphicsView::saveAs(QString path)
{
    std::ofstream fout(path.toStdString());
    int n = (components.getSize());
    fout.write((char*)&n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        int id = components[i]->id();
        fout.write((char*)&id, sizeof(int));
        components[i]->writeBinary(fout);
    }

    n = wires->childItems().size();
    fout.write((char*)&n, sizeof(int));
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->group() == wires) {
            QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem*>(item);
            QLineF l = line->line();
            double d;
            d = l.p1().x(); fout.write((char*)&d, sizeof(double));
            d = l.p1().y(); fout.write((char*)&d, sizeof(double));
            d = l.p2().x(); fout.write((char*)&d, sizeof(double));
            d = l.p2().y(); fout.write((char*)&d, sizeof(double));
        }
    }
    n = connections->childItems().size();
    fout.write((char*)&n, sizeof(int));
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->group() == connections) {
            QGraphicsEllipseItem *ellipse = dynamic_cast<QGraphicsEllipseItem*>(item);
            double x = ellipse->rect().x();
            double y = ellipse->rect().y();
            fout.write((char*)&x, sizeof(double));
            fout.write((char*)&y, sizeof(double));
        }
    }
    fout.close();

    this->path = path;
    saved = true;
    emit savedStateChanged();
}

void GraphicsView::open(QString path)
{
    components.clear();
    std::ifstream fin(path.toStdString());
    std::shared_ptr<Component> t;
    int n;
    fin.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        int id;
        fin.read((char*)&id, sizeof(int));
        switch (id){
        case 3:
            t = std::shared_ptr<Component>(new GND());
            break;
        case 4:
            t = std::shared_ptr<Component>(new NetLabel());
            break;
        case 5:
            t = std::shared_ptr<Component>(new TwoInputAndGate());
            break;
        case 6:
            t = std::shared_ptr<Component>(new TwoInputNandGate());
            break;
        case 7:
            t = std::shared_ptr<Component>(new TwoInputOrGate());
            break;
        case 8:
            t = std::shared_ptr<Component>(new TwoInputNorGate());
            break;
        case 9:
            t = std::shared_ptr<Component>(new NotGate());
            break;
        case 10:
            t = std::shared_ptr<Component>(new TwoInputXorGate());
            break;
        case 11:
            t = std::shared_ptr<Component>(new Resistor());
            break;
        case 12:
            t = std::shared_ptr<Component>(new Capacitor());
            break;
        case 13:
            t = std::shared_ptr<Component>(new LogicBlock());
            break;
        }
        t->readBinary(fin);
        components.push_back(t);
        t.reset();
    }
    fin.read((char*)&n, sizeof(int));
    double x1, x2, y1, y2;
    for (int i = 0; i < n; ++i) {
        fin.read((char*)&x1, sizeof(double));
        fin.read((char*)&y1, sizeof(double));
        fin.read((char*)&x2, sizeof(double));
        fin.read((char*)&y2, sizeof(double));
        wires->addToGroup(scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 3)));
    }

    fin.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        fin.read((char*)&x1, sizeof(double));
        fin.read((char*)&y1, sizeof(double));
        connections->addToGroup(scene->addEllipse(x1, y1,
                       6, 6, QPen(Qt::black, 3), QBrush(Qt::black)));
    }

    fin.close();
    this->path = path;
    saved = true;
    emit savedStateChanged();
}

void GraphicsView::addLabel(const QString &str, double x, double y,
                            const QColor &color, double scale,
                            int align, int valign)
{
    QGraphicsTextItem *io = new QGraphicsTextItem;
    io->setFont(QFont("Courier New", 8));
    io->setScale(scale);
    io->setPlainText(str);
    if (align > 0)
        x -= io->boundingRect().width()*scale;
    else if (align == 0)
        x -= io->boundingRect().width()*scale/2;
    if (valign > 0)
        y -= io->boundingRect().height()*scale;
    else if (valign == 0)
        y -= io->boundingRect().height()*scale/2;
    io->setPos(x, y);
    io->setDefaultTextColor(color);
    io->setZValue(7);
    scene->addItem(io);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        _pan = true;
        _panStartX = event->x();
        _panStartY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    } else if (event->button() == Qt::LeftButton && nodeToAdd == 0
               && nowMoving == -1) {
        int i = hoveredNode(event);
        if (i > -1) {
            nowMoving = i;
            lastPoint.setX(components[i]->ex());
            lastPoint.setY(components[i]->ey());
            tmp = components[i];
        }
    }
    event->ignore();
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    std::shared_ptr<Component> t;
    TextDialog td;
    QPointF pt = mapToScene(event->pos());
    snapToGrid(&pt);

    if (event->button() == Qt::MiddleButton) {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    } else if (event->button() == Qt::LeftButton) {
        if (nowMoving > -1) {
            components[nowMoving].get()->setPos(tmp.get()->ex(), tmp.get()->ey());
            nowMoving = -1;
            tmp.reset();
            saved = false;
            emit savedStateChanged();
        } else if (nodeToAdd != 0){
            QPoint newPoint;
            switch (nodeToAdd) {
            case 1:
                if (!_line) {
                    newPoint = QPoint(pt.x(), pt.y());
                    _line = true;
                } else {
                    double dx = abs(lastPoint.x()-pt.x());
                    double dy = abs(lastPoint.y()-pt.y());
                    if (dx < dy)
                        newPoint = QPoint(lastPoint.x(), pt.y());
                    else {
                        newPoint = QPoint(pt.x(), lastPoint.y());
                    }
                    wires->addToGroup(scene->addLine(lastPoint.x(), lastPoint.y(),
                                   newPoint.x(), newPoint.y(), QPen(Qt::black, 3)));
                }
                lastPoint = newPoint;
                break;
            case 2:
                connections->addToGroup(scene->addEllipse(pt.x()-3, pt.y()-3,
                               6, 6, QPen(Qt::black, 3), QBrush(Qt::black)));
                nodeToAdd = 0;
                break;
            case 4:
                if (td.exec() == QDialog::Accepted) {
                    QString text;
                    text = td.getText();
                    tmp->setText(text);
                    components.push_back(tmp);
                    tmp.reset();
                }
                nodeToAdd = 0;
                break;
            case 13:
                snapToGrid(&pt, 50);
                if (!_line) {
                    newPoint = QPoint(pt.x(), pt.y());
                    _line = true;
                } else {
                    newPoint = QPoint(pt.x(), pt.y());
                    if (newPoint.x() < lastPoint.x()) {
                        int t = newPoint.x();
                        newPoint.setX(lastPoint.x());
                        lastPoint.setX(t);
                    }
                    if (newPoint.y() < lastPoint.y()) {
                        int t = newPoint.y();
                        newPoint.setY(lastPoint.y());
                        lastPoint.setY(t);
                    }
                    double w = newPoint.x() - lastPoint.x(),
                           h = newPoint.y() - lastPoint.y(),
                           ex = newPoint.x(),
                           ey = newPoint.y() - h/2;
                    if (w > 5 && h > 5) {
                        tmp = std::shared_ptr<Component>(new LogicBlock(ex, ey, 0, w, h));
                        if (td.exec() == QDialog::Accepted) {
                            QString text;
                            text = td.getText();
                            tmp->setText(text);
                        }
                        components.push_back(tmp);
                        tmp.reset();
                    }
                    _line = false;
                    nodeToAdd = 0;
                }
                lastPoint = newPoint;
                break;
            default:
                if (tmp.get()) {
                    components.push_back(tmp);
                    tmp.reset();
                }
                nodeToAdd = 0;
            }
            saved = false;
            emit savedStateChanged();
        }
    } else if (event->button() == Qt::RightButton) {
        if (nowMoving < 0) {
            if (nodeToAdd == 0) {
                foreach(QGraphicsItem *item, scene->items()) {
                    double x = item->boundingRect().topLeft().x()-10,
                           y = item->boundingRect().topLeft().y()-10,
                           w = item->boundingRect().width()+20,
                           h = item->boundingRect().height()+20;
                    if ((item->group() == connections || item->group() == wires)
                            && pt.x() > x && pt.y() > y
                            && pt.x() < (x+w) && pt.y() < (y+h)) {
                        delete item;
                        saved = false;
                        emit savedStateChanged();
                    }
                }
                int i = hoveredNode(event);
                if (i > -1) {
                    components.del(i);
                    saved = false;
                    emit savedStateChanged();
                }
            } else if (nodeToAdd == 1) {
                _line = false;
                saved = false;
                emit savedStateChanged();
            }
            nodeToAdd = 0;
        } else {
            components[nowMoving].get()->setPos(lastPoint.x(), lastPoint.y());
            components[nowMoving].get()->setRotation(tmp.get()->r());
            components[nowMoving].get()->setText(tmp.get()->getText());
            nowMoving = -1;
            tmp.reset();
            nodeToAdd = 0;
        }
    }
    event->ignore();
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R && (nodeToAdd || nowMoving > -1))
        tmp.get()->rotate();
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (_pan) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        _panStartX = event->x();
        _panStartY = event->y();
        event->accept();
        return;
    } else if (nodeToAdd == 0 && nowMoving < 0) {
        int hov = hoveredNode(event);
        for (int j = 0; j < (int)components.getSize(); ++j) {
            if (j == hov)
                components[j].get()->setHover(true);
            else
                components[j].get()->setHover(false);
        }
    } else if ((nodeToAdd > 2 && nodeToAdd < 13) || nowMoving > -1) {
        QPointF pt = mapToScene(event->pos());
        snapToGrid(&pt);
        tmp.get()->setPos(pt.x(), pt.y());
    }
    event->ignore();
}

void GraphicsView::slotAlarmTimer()
{
    //qDebug() << "node " << nodeToAdd << " line " << _line << " move " << nowMoving;
    foreach(QGraphicsItem *item, scene->items()) {
        if (item != grid && item->group() != grid &&
                item != connections && item->group() != connections &&
                item != wires && item->group() != wires)
            delete item;
    }
    for (size_t i = 0; i < components.getSize(); ++i) {
        components[i].get()->draw(scene);
    }
    if ((nodeToAdd > 2 && nodeToAdd < 13) || nowMoving > -1) {
        if (tmp.get())
            tmp->draw(scene);
    }
}

void GraphicsView::addGrid()
{
    QPointF bl = scene->sceneRect().bottomLeft(),
            tr = scene->sceneRect().topRight();
    for (double x = bl.x(); x <= tr.x(); x += 25) {
        grid->addToGroup(scene->addLine(x, bl.y(), x, tr.y(), QPen(Qt::lightGray)));
    }
    for (double y = tr.y(); y <= bl.y(); y += 25) {
        grid->addToGroup(scene->addLine(bl.x(), y, tr.x(), y, QPen(Qt::lightGray, .5)));
    }
}

void GraphicsView::removeGrid()
{
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->group() == grid)
            delete item;
    }
}

void GraphicsView::snapToGrid(QPointF *pt, double step) const
{
    pt->setX(round(pt->x()/step)*step);
    pt->setY(round(pt->y()/step)*step);
}

int GraphicsView::hoveredNode(QMouseEvent *event) const
{
    QPointF pt = mapToScene(event->pos());
    for (size_t i = 0; i < components.getSize(); ++i) {
        if (components[i].get()->hover(pt.x(), pt.y()))
            return i;
    }
    return -1;
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int i = hoveredNode(event);
        LogicBlock *l = dynamic_cast<LogicBlock*>(components[i].get());
        NetLabel *n = dynamic_cast<NetLabel*>(components[i].get());
        TextDialog td;
        if ((l || n) && td.exec() == QDialog::Accepted) {
            QString text = td.getText();
            components[i].get()->setText(text);
            saved = false;
            emit savedStateChanged();
        }
    }
}

