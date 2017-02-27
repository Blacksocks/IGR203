#include <QState>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initParams()
{
    hours = 0;
    minutes = 0;
    ratioTimeWeight = 0;
    mode = MICRO_WAVE;
    resetParams();
}

void MainWindow::resetParams()
{
    power = 100;
    duration = 60;
}

void MainWindow::changeMode()
{
    switch(mode)
    {
    case MICRO_WAVE: mode = GRILL; break;
    case GRILL: mode = BOTH; break;
    case BOTH: mode = MICRO_WAVE; break;
    default: mode = MICRO_WAVE;
    }
}

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
#ifdef DEBUG
    connect(init,       SIGNAL(entered()), this, SLOT(initEnter()));
    connect(clockSet1,  SIGNAL(entered()), this, SLOT(clockSet1Enter()));
    connect(clockSet2,  SIGNAL(entered()), this, SLOT(clockSet2Enter()));
    connect(powerSet,   SIGNAL(entered()), this, SLOT(powerSetEnter()));
    connect(modeSet,    SIGNAL(entered()), this, SLOT(modeSetEnter()));
    connect(timeSet,    SIGNAL(entered()), this, SLOT(timeSetEnter()));
    connect(defrost,    SIGNAL(entered()), this, SLOT(defrostEnter()));
    connect(cooking,    SIGNAL(entered()), this, SLOT(cookingEnter()));
#endif
    connect(clockSet1,  SIGNAL(exited()), this, SLOT(clockSet1Exit()));
    connect(clockSet2,  SIGNAL(exited()), this, SLOT(clockSet2Exit()));
    connect(powerSet,   SIGNAL(exited()), this, SLOT(powerSetExit()));
    connect(modeSet,    SIGNAL(exited()), this, SLOT(modeSetExit()));
    connect(timeSet,    SIGNAL(exited()), this, SLOT(timeSetExit()));
    connect(defrost,    SIGNAL(exited()), this, SLOT(defrostExit()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initParams();
    ui->setupUi(this);
    QStateMachine * stateM = new QStateMachine();
    initStateMachine(stateM);
    stateM->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clockSet1Exit()
{
    hours = ui->dial->value();
#ifdef DEBUG
    qDebug() << "hours: " << hours;
#endif
}

void MainWindow::clockSet2Exit()
{
    minutes = ui->dial->value();
#ifdef DEBUG
    qDebug() << "minutes: " << minutes;
#endif
}

void MainWindow::powerSetExit()
{
    power = ui->dial->value();
#ifdef DEBUG
    qDebug() << "power: " << power;
#endif
}

void MainWindow::modeSetExit()
{
    changeMode();
}

void MainWindow::timeSetExit()
{
    duration = ui->dial->value();
#ifdef DEBUG
    qDebug() << "duration: " << duration;
#endif
}

void MainWindow::defrostExit()
{
    duration = ratioTimeWeight * ui->dial->value();
#ifdef DEBUG
    qDebug() << "duration: " << duration;
#endif
}

void MainWindow::on_dial_valueChanged(int value)
{
    ui->lineEdit->setText(QString::number(value));
}

void MainWindow::initEnter()
{
    ui->lineEdit->setText(QString::number(hours) + ":" + QString::number(minutes));
#ifdef DEBUG
    qDebug() << "initEnter";
#endif
}

void MainWindow::clockSet1Enter()
{
    int newVal = 24 * ui->dial->value() / ui->dial->maximum();
    ui->dial->setRange(0, 24);
    ui->dial->setValue(newVal);
    ui->lineEdit->setText(QString::number(ui->dial->value()));
#ifdef DEBUG
    qDebug() << "clockSet1Enter";
#endif
}

void MainWindow::clockSet2Enter()
{
    int newVal = 60 * ui->dial->value() / ui->dial->maximum();
    ui->dial->setRange(0, 60);
    ui->dial->setValue(newVal);
    ui->lineEdit->setText(QString::number(ui->dial->value()));
#ifdef DEBUG
    qDebug() << "clockSet2Enter";
#endif
}

void MainWindow::powerSetEnter()
{
    int newVal = 100 * ui->dial->value() / ui->dial->maximum();
    ui->dial->setRange(0, 100);
    ui->dial->setValue(newVal);
    ui->lineEdit->setText(QString::number(ui->dial->value()));
#ifdef DEBUG
    qDebug() << "powerSetEnter";
#endif
}

void MainWindow::timeSetEnter()
{
    int newVal = 360 * ui->dial->value() / ui->dial->maximum();
    ui->dial->setRange(0, 360);
    ui->dial->setValue(newVal);
    ui->lineEdit->setText(QString::number(ui->dial->value()));
#ifdef DEBUG
    qDebug() << "timeSetEnter";
#endif
}

void MainWindow::defrostEnter()
{
    int newVal = 100 * ui->dial->value() / ui->dial->maximum();
    ui->dial->setRange(0, 100);
    ui->dial->setValue(newVal);
    ui->lineEdit->setText(QString::number(ratioTimeWeight * ui->dial->value()));
#ifdef DEBUG
    qDebug() << "defrostEnter";
#endif
}
