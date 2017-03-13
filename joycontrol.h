#ifndef JOYCONTROL_H
#define JOYCONTROL_H

#include <QMainWindow>
#include <QDebug>
#include "stdafx.h"
#include "inc/public.h"
#include "inc/vjoyinterface.h"

#define DEV_ID 1

namespace Ui {
class JoyControl;
}

class JoyControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoyControl(QWidget *parent = 0);
    int connectToJoystick(void);
    ~JoyControl();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::JoyControl *ui;
};

#endif // JOYCONTROL_H
