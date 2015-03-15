#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "qcsvmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();
protected:
    void initModel();
    void initActions();
    // register classes, that can be loaded from csv
    // this function should be changed to add new class
    void registerClasses();
private:
    Ui::MainWindow *ui;
    QCSVModel *m_model;
    QList<QObject *> m_objects;
};

#endif // MAINWINDOW_H
