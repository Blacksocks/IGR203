#include <QState>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initStateMachine(QStateMachine * stateM)
{
    QState * stopGroup = new QState();
    QState * init = new QState(stopGroup);
    QState * clockSet1 = new QState(stopGroup);
    QState * clockSet2 = new QState(stopGroup);
    QState * powerSet = new QState(stopGroup);
    QState * modeSet = new QState(stopGroup);
    QState * timeSet = new QState(stopGroup);
    QState * defrost = new QState(stopGroup);
    QState * cooking = new QState(stopGroup);
    init->addTransition(ui->clockBtn,       SIGNAL(clicked()),  clockSet1);
    init->addTransition(ui->powerBtn,       SIGNAL(clicked()),  powerSet);
    init->addTransition(ui->modeBtn,        SIGNAL(clicked()),  modeSet);
    init->addTransition(ui->defrostBtn,     SIGNAL(clicked()),  defrost);
    init->addTransition(ui->startBtn,       SIGNAL(clicked()),  cooking);
    clockSet1->addTransition(ui->clockBtn,  SIGNAL(clicked()),  clockSet2);
    clockSet2->addTransition(ui->clockBtn,  SIGNAL(clicked()),  init);
    powerSet->addTransition(ui->powerBtn,   SIGNAL(clicked()),  timeSet);
    modeSet->addTransition(ui->modeBtn,     SIGNAL(clicked()),  timeSet);
    timeSet->addTransition(ui->startBtn,    SIGNAL(clicked()),  cooking);
    defrost->addTransition(ui->startBtn,    SIGNAL(clicked()),  cooking);
    //cooking->addTransition(sender,        onTimeout,          init);
    stopGroup->addTransition(ui->stopBtn,   SIGNAL(clicked()),  init);
    // set state machine
    stateM->addState(stopGroup);
    stopGroup->setInitialState(init);
    stateM->setInitialState(stopGroup);
    connect(init,       SIGNAL(entered()), this, SLOT(initEnter()));
    connect(clockSet1,  SIGNAL(entered()), this, SLOT(clockSet1Enter()));
    connect(clockSet2,  SIGNAL(entered()), this, SLOT(clockSet2Enter()));
    connect(powerSet,   SIGNAL(entered()), this, SLOT(powerSetEnter()));
    connect(modeSet,    SIGNAL(entered()), this, SLOT(modeSetEnter()));
    connect(timeSet,    SIGNAL(entered()), this, SLOT(timeSetEnter()));
    connect(defrost,    SIGNAL(entered()), this, SLOT(defrostEnter()));
    connect(cooking,    SIGNAL(entered()), this, SLOT(cookingEnter()));
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStateMachine * stateM = new QStateMachine();
    initStateMachine(stateM);
    stateM->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clockBtn_clicked(){qDebug() << "on_clockBtn_clicked";}
void MainWindow::on_powerBtn_clicked(){qDebug() << "on_powerBtn_clicked";}
void MainWindow::on_modeBtn_clicked(){qDebug() << "on_modeBtn_clicked";}
void MainWindow::on_defrostBtn_clicked(){qDebug() << "on_defrostBtn_clicked";}
void MainWindow::on_startBtn_clicked(){qDebug() << "on_startBtn_clicked";}
void MainWindow::on_stopBtn_clicked(){qDebug() << "on_stopBtn_clicked";}
