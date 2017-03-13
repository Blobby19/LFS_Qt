#include "lfs.h"
#include "ui_lfs.h"
//#include "joycontrol.h"


/**
 * Constructor of the appalication
 * @brief LFS::LFS
 * @param parent
 */
LFS::LFS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LFS)
{
    ui->setupUi(this);
    statusLabel = new QLabel(this);

    statusLabel->setText("Non connécté");

    scene = new QGraphicsScene(this);
    ui->gvAccel->setScene(scene);

    sceneHeading = new QGraphicsScene(this);
    ui->gvHeading->setScene(sceneHeading);

    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    line = scene->addLine(50, 50, 100, 100, blackPen);
    ellipse = scene->addEllipse(50, 50, 4, 4, blackPen, redBrush);
    ui->statusBar->addPermanentWidget(statusLabel);

    lineHeading = sceneHeading->addLine(50, 50, 50, 50, blackPen);
    ellipseHeading = sceneHeading->addEllipse(0, 0, 100, 100);
}

/**
 * Destroy LFS
 * @brief LFS::~LFS
 */
LFS::~LFS()
{
    delete ui;
}

/**
 * Exit of the application
 * @brief LFS::on_actionQuitter_triggered
 */
void LFS::on_actionQuitter_triggered()
{
    qApp->quit();
}

/**
 * Update View of Gauges of the car
 * @brief LFS::updateOutgauge
 * @param data
 */
void LFS::updateOutgauge(const OutGaugePack data){
    ui->lcdSpeed->display(data.Speed*3.6);
    ui->lcdRPM->display(data.RPM);
    ui->pbThrottle->setValue(data.Throttle*100);
    ui->pbBrake->setValue(data.Brake*100);
    ui->pbClutch->setValue(data.Clutch*100);
    ui->labelCar->setText(data.Car);
    ui->pbTurbo->setValue(((data.Turbo+1)/3)*100);
    ui->pbFuel->setValue(data.Fuel*100);
    if(data.Gear==0)
        ui->lcdGear->display(QString('R'));
    else
        ui->lcdGear->display(data.Gear-1);
    unsigned dashLights = data.DashLights & data.ShowLights;
    //bool shift = (dashLights>>DL_SHIFT)&0x1;

    //bool fullbeam = (dashLights>>DL_FULLBEAM)&0x1;
    //bool handbrake = (dashLights>>DL_HANDBRAKE)&0x1;
    //bool pitspeed = (dashLights>>DL_PITSPEED)&0x1;
    //bool tc = (dashLights>>DL_TC)&0x1;
    bool right = (dashLights>>DL_SIGNAL_R)&0x1;
    bool left = (dashLights>>DL_SIGNAL_L)&0x1;
    bool warnings = (dashLights>>DL_SIGNAL_ANY)&0x1;
    bool warningEnabled = (data.DashLights>>DL_SIGNAL_ANY)&0x1;
    if(warningEnabled){
        ui->imgLeftSignal->setEnabled(warnings);
        ui->imgRightSignal->setEnabled(warnings);
    }
    else{
        ui->imgLeftSignal->setEnabled(left);
        ui->imgRightSignal->setEnabled(right);
    }


    bool abs = (dashLights >> DL_ABS)&0x1;
    ui->imgAbs->setEnabled(abs);
    //bool battery = (dashLights>>DL_BATTERY)&0x1;
    //bool oilwarn = (dashLights>>DL_OILWARN)&0x1;
}

void LFS::updateOutsim(const OutSimPack data){
    float accelX = data.Accel.X*cos(-data.Heading) - data.Accel.Y*sin(-data.Heading);
    float accelY = data.Accel.X*sin(-data.Heading) + data.Accel.Y*cos(-data.Heading);
    line->setLine(50, 50, 50-accelX*10, 50+accelY*10);
    ellipse->setX(-accelX*10-2);
    ellipse->setY(accelY*10-2);

    float xHeading = 50+50*(cos(data.Heading)*cos(-M_PI/2) - sin(data.Heading) * sin(-M_PI/2));
    float yHeading = 50+50*(cos(data.Heading)*sin(-M_PI/2) + sin(data.Heading) * cos(-M_PI/2));
    lineHeading->setLine(50, 50, xHeading, yHeading);
    //qDebug() << accelX/9.81 << " - " << accelY/9.81;
    qDebug()<<data.Heading << " - " <<accelX;
}

void LFS::on_actionOpen_triggered()
{
    UDPSocket* client_outgauge = new UDPSocket(0, 29967);
    UDPSocket* client_outsim = new UDPSocket(0, 29966);

    connect(client_outgauge, SIGNAL(updateUIOutgauge(OutGaugePack)), this, SLOT(updateOutgauge(OutGaugePack)));
    connect(client_outsim, SIGNAL(updateUIOutsim(OutSimPack)), this, SLOT(updateOutsim(OutSimPack)));
    statusLabel->setText("Connecté");

}

void LFS::on_actionSave_triggered(){

}

void LFS::on_actionJoyControl_triggered(){

}
