#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <stdio.h>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initStateMachine(QStateMachine * stateM);
    ~MainWindow();
public slots:
    void initEnter(){qDebug() << "init state enter";}
    void clockSet1Enter(){qDebug() << "clockSet1 state enter";}
    void clockSet2Enter(){qDebug() << "clockSet2 state enter";}
    void powerSetEnter(){qDebug() << "powerSet state enter";}
    void modeSetEnter(){qDebug() << "modeSet state enter";}
    void timeSetEnter(){qDebug() << "timeSet state enter";}
    void defrostEnter(){qDebug() << "defrost state enter";}
    void cookingEnter(){qDebug() << "cooking state enter";}

private slots:
    void on_clockBtn_clicked();
    void on_powerBtn_clicked();
    void on_modeBtn_clicked();
    void on_startBtn_clicked();
    void on_defrostBtn_clicked();
    void on_stopBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
