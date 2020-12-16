#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addElement(int id);
    void createCircuit();
    void openCircuit();
    void exportCircuit();
    void saveCircuit();
    void saveCircuitAs();
    void exit();

private:
    Ui::MainWindow *ui;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    void createActions();
    void createMenus();
    void updateSavedLabel();
    void updateActionLabel();
    bool askForSave();
    QString path;
    GraphicsView *chart;
    QLabel *savedLabel;
    //QLabel *actionLabel;
    QMenu *fileMenu;
    QAction *newAct;
    QAction *exportAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
};
#endif // MAINWINDOW_H
