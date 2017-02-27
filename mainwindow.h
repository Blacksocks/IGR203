#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <stdio.h>
#include <QDebug>

#define DEBUG       1

enum Mode {MICRO_WAVE, GRILL, BOTH};

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initStateMachine(QStateMachine * stateM);
    void initParams();
    void resetParams();
    void changeMode();
    ~MainWindow();

private slots:
#ifdef DEBUG
    // on state entered
    void initEnter();
    void clockSet1Enter();
    void clockSet2Enter();
    void powerSetEnter();
    void modeSetEnter(){qDebug() << "modeSetEnter";}
    void timeSetEnter();
    void defrostEnter();
    void cookingEnter(){qDebug() << "cookingEnter";}
    // on button clicked
    void on_clockBtn_clicked(){qDebug() << "on_clockBtn_clicked";}
    void on_powerBtn_clicked(){qDebug() << "on_powerBtn_clicked";}
    void on_modeBtn_clicked(){qDebug() << "on_modeBtn_clicked";}
    void on_startBtn_clicked(){qDebug() << "on_startBtn_clicked";}
    void on_defrostBtn_clicked(){qDebug() << "on_defrostBtn_clicked";}
    void on_stopBtn_clicked(){qDebug() << "on_stopBtn_clicked";}
#endif
    // dial changed
    void on_dial_valueChanged(int value);
    // on state exited
    void clockSet1Exit();
    void clockSet2Exit();
    void powerSetExit();
    void modeSetExit();
    void timeSetExit();
    void defrostExit();

private:
    Ui::MainWindow *ui;
    int power;
    int duration;
    int hours;
    int minutes;
    int ratioTimeWeight;
    Mode mode;
};

#endif // MAINWINDOW_H
