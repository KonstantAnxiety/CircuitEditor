#include "netlabel.h"

#include <QGraphicsItem>
#include <math.h>

void NetLabel::draw(QGraphicsScene *scene)
{
    EndComponent::draw(scene);
    QGraphicsTextItem *io = new QGraphicsTextItem;
    io->setFont(QFont("Courier New", 18));
    io->setPlainText(getText());
    if (io->boundingRect().width() > w())
        setW(round((io->boundingRect().width()+25)/25)*25);
    double x = ex();
    double y = ey();

    if ((int)r() % 360 == 90) {
        io->setRotation(-90);
        x -= io->boundingRect().height()*.5;
        y += (io->boundingRect().width()+25);
    } else if ((int)r() % 360 == 180) {
        io->setRotation(0);
        x -= (io->boundingRect().width()+25);
        y -= (io->boundingRect().height()*.5);
    } else if ((int)r() % 360 == 270) {
        io->setRotation(-90);
        x -= io->boundingRect().height()*.5;
        y -= (25);
    } else if ((int)r() % 360 == 0) {
        io->setRotation(0);
        x += (25);
        y -= (io->boundingRect().height()*.5);
    }

    io->setPos(x, y);
    io->setZValue(14);
    scene->addItem(io);
}
