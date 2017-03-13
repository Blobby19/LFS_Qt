#ifndef LFS_H
#define LFS_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QTCore/qmath.h>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "stdint.h"
#include "InSim.h"
#include "udpsocket.h"

namespace Ui {
    class LFS;
}

class LFS : public QMainWindow
{
    Q_OBJECT

public:
    explicit LFS(QWidget *parent = 0);
    ~LFS();

private slots:
    void on_actionQuitter_triggered();
    void updateOutgauge(const OutGaugePack data);
    void updateOutsim(const OutSimPack data);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionJoyControl_triggered();

private:
    Ui::LFS *ui;
    QLabel *statusLabel;
    QGraphicsScene *scene;
    QGraphicsLineItem *line;
    QGraphicsEllipseItem *ellipse;
    QGraphicsScene *sceneHeading;
    QGraphicsLineItem *lineHeading;
    QGraphicsEllipseItem *ellipseHeading;
};

#endif // LFS_H
