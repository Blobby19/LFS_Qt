#include "lfs.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Starting Application";
    LFS lfs_view;
    lfs_view.show();
    return a.exec();
}
