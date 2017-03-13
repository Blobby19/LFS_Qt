#include "udpsocket.h"

UDPSocket::UDPSocket(QObject *parent, int _port) : QObject(parent)
{
    port = _port;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, port);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UDPSocket::helloUDP(){
    QByteArray Data;
    Data.append("Hello from UDP !");
    socket->writeDatagram(Data, QHostAddress::LocalHost, 29967);
}

void UDPSocket::readyRead(){
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    const void* poTemp = (const void*)buffer.constData();
    if(port==29967){
        const OutGaugePack* data = static_cast<const OutGaugePack*>(poTemp);
        updateUIOutgauge(*data);
    }
    else{
        const OutSimPack* data = static_cast<const OutSimPack*>(poTemp);
        updateUIOutsim(*data);
    }
}
