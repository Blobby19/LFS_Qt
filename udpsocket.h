#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>
#include <lfs.h>

class UDPSocket : public QObject
{
    Q_OBJECT
public:
    explicit UDPSocket(QObject *parent = 0, int port = 29967);
    void helloUDP();

signals:
    void updateUIOutgauge(const OutGaugePack data);
    void updateUIOutsim(const OutSimPack data);

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    int port;
};

#endif // UDPSOCKET_H
