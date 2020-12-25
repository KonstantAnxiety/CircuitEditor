#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (QApplication::arguments().size() > 1) {
        const QString FILENAME = QApplication::arguments().at(1);
        w.openFile(FILENAME);
    }
    w.show();
    return a.exec();
}
