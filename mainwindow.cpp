#include <QMetaObject>
#include <QMetaProperty>
#include <QFileDialog>
#include <QActionGroup>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsampleclass.h"
#include "qdummyclass.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    registerClasses();
    initModel();
    initActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("CSV (*.csv)"));

    if (!fileName.isEmpty()) {
        m_model->setFilename(fileName);
        if (m_model->parse())
            ui->statusBar->showMessage("CSV loaded");
    }
}

void MainWindow::initModel()
{
    m_model = new QCSVModel();
    connect(m_model, SIGNAL(error(QString)), ui->statusBar, SLOT(showMessage(QString)));
    ui->tableView->setModel(m_model);
}


void MainWindow::initActions()
{
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    for ( int i = 0 ; i < m_objects.size() ; i++ ) {
        const QMetaObject *meta = m_objects.at(i)->metaObject();
        QAction *action = new QAction(meta->className(), this);
        action->setCheckable(true);
        ui->menuObject->addAction(action);
        actionGroup->addAction(action);
        connect(action, &QAction::toggled, [i, this](){ m_model->setObject(m_objects.at(i)); });
    }
    actionGroup->actions().at(0)->setChecked(true);
}

void MainWindow::registerClasses()
{
    m_objects
            << new QSampleClass()
            << new QDummyClass();
}
