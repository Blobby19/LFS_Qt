#include "joycontrol.h"
#include "ui_joycontrol.h"

JoyControl::JoyControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoyControl)
{
    ui->setupUi(this);
}

JoyControl::~JoyControl()
{
    delete ui;
}

int JoyControl::connectToJoystick(){
    int stat = 0;
    uint DevID=DEV_ID;
    ushort X = 0;
    ushort Y = 0;
    ushort Z = 0;
    long btns = 0;

    _JOYSTICK_POSITION iReport;

    PVOID pPositionMessage;
    uint IoCode = LOAD_POSITIONS;
    uint IoSize = sizeof(JOYSTICK_POSITION);
    BYTE id = 1;
    uint iInterface = 1;

    if(!vJoyEnabled()){
        qDebug()<<"vJoyEnabled failed - make sure that vJoy is installed and enabled!";
        int dummy = getchar();
        stat = -2;
        return -1;
    }
    else{
        qDebug()<<"VendorProduct: "<<static_cast<TCHAR*>(GetvJoyManufacturerString());
    }

    VjdStat status = GetVJDStatus(DevID);

    switch(status){
        case VJD_STAT_OWN:
            qDebug()<<"vJoy device "<<DevID<<" is already owned";
            break;
        case VJD_STAT_FREE:
            qDebug()<<"vJoy device "<<DevID<<" is free";
            break;
        case VJD_STAT_BUSY:
            qDebug()<<"vJoy device "<<DevID<<" is busy";
            return -1;
        case VJD_STAT_MISS:
            qDebug()<<"vJoy device "<<DevID<<" is not installed!";
            return -1;
        default:
            qDebug()<<"vJoy device "<<DevID<<" is in error mode!";
            return -1;
    }

    if(!AcquireVJD(DevID)){
        qDebug()<<"Failed to acquire vJoy device number "<<DevID;
        int dummy = getchar();
        stat = -1;
        return -1;
    }
    else{
        qDebug()<<"Acquired device number "<<DevID <<" OK!";
    }


    /*while(1){
        id = (BYTE)DevID;
        iReport.bDevice = id;
        if(Z<35000)Z=0;
        Z+=200;
        iReport.wAxisZ=Z;
        iReport.wAxisX=1000;
        iReport.wAxisY = Z/2+7000;

        pPositionMessage = (PVOID)(&iReport);
        qDebug()<<pPositionMessage;
        if(!UpdateVJD(DevID, pPositionMessage)){
            qDebug()<<"Feeding vJoy device number "<<DevID<< " failed!";
            getchar();
            AcquireVJD(DevID);
        }
        //Sleep(2);
    }
    RelinquishVJD(DevID);*/

}

void JoyControl::on_btnConnect_clicked()
{
    connectToJoystick();
}
