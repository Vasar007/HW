#include <iostream>
#include <thread>

#include "Client.h"


namespace vasily
{

Client::Client(const quint16 serverPort, const std::string& serverIP, QObject* parent)
    : QObject(parent),
      _serverPort(serverPort),
      _socket(std::make_unique<QTcpSocket>(this)),
      _serverIP(serverIP)
{
    qDebug() << "Server Port:" << serverPort << "\nLayer IP:" << serverIP.c_str() << '\n';

    connect(_socket.get(), &QTcpSocket::readyRead, this, &Client::slotReadFromServer);

    connect(_socket.get(), &QTcpSocket::disconnected, this, &Client::slotServerDisconnected,
            Qt::QueuedConnection);

    connect(this, &Client::signalToSend, this, &Client::slotSendDataToServer);
}

void Client::slotReadFromServer() const
{
    if (_socket->bytesAvailable() > 0)
    {
        const QByteArray array = _socket->readAll();
        const std::string receivedData = array.toStdString();

        qDebug() << _socket->localPort() << '-' << array << '\n';
    }
}

void Client::slotServerDisconnected() const
{
    qDebug() << "\nServer disconnected!\n";
    tryReconnect();
}

void Client::slotSendDataToServer(const QByteArray& data) const
{
    _socket->write(data);
    qDebug() << "Sent data:" << data << "successfully.\n";
}

void Client::run()
{
    std::thread workThread(&Client::waitLoop, this);
    workThread.detach();
}

void Client::waitLoop() const
{
    qDebug() << "\nWaiting for reply...\n\n";

    while (true)
    {
        std::string input;
        qDebug() << "Enter command: ";
        std::getline(std::cin, input);

        if (!input.empty())
        {
            sendData(input);
        }
    }
}

bool Client::tryConnect(const quint16 port, const std::string& ip, QTcpSocket* socketToConnect,
                        const int msecs) const
{
    if (socketToConnect->isOpen())
    {
        socketToConnect->close();
    }

    socketToConnect->connectToHost(ip.c_str(), port);

    if (socketToConnect->waitForConnected(msecs))
    {
        qDebug() << "Connected to Server!\n";
        return true;
    }

    qDebug() << "Not connected to Server!\n";
    return false;
}

void Client::tryReconnect() const
{
    launch();
}

void Client::launch() const
{
    bool isConnected = tryConnect(_serverPort, _serverIP, _socket.get(), true);
    while (!isConnected)
    {
        isConnected = tryConnect(_serverPort, _serverIP, _socket.get(), true);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    qDebug() << "\nClient launched...\n";
}

void Client::sendData(const std::string& data) const
{
    emit signalToSend(data.c_str());
}


} // namespace vasily
