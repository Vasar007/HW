#include "Server.h"


namespace vasily
{

Server::Server(const quint16 port, QObject* parent)
    : QObject(parent),
      _port(port),
      _socket(std::make_unique<QTcpServer>(this)),
      _clientSocket(nullptr)
{
    qDebug() << "Receiving Port:" << port << '\n';
    connect(_socket.get(), &QTcpServer::newConnection, this, &Server::slotNewConnection);
}

void Server::slotNewConnection()
{
    qDebug() << "\nNew connection to server\n";

    _clientSocket = _socket->nextPendingConnection();
    _clientSocket->write("Test message from Server.\n");

    connect(_clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadFromClient);
    connect(_clientSocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
}

void Server::slotReadFromClient() const
{
    if (_clientSocket->bytesAvailable() > 0)
    {
        QByteArray array = _clientSocket->readAll();
        qDebug() << array << '\n';

        const std::string receivedData = array.toStdString();
        _clientSocket->write(receivedData.c_str());
    }
}


void Server::slotClientDisconnected() const
{
    qDebug() <<  "Client disconnected from port!\n";
    _clientSocket->close();
}

void Server::launch() const
{
    if (_socket->listen(QHostAddress("172.17.0.5"), _port))
    {
        qDebug() << "Server is started!\n";
    }
    else
    {
        qDebug() << "Server is not started!\n";
    }

    qDebug() << "\nWaiting for reply...\n";
}

} // namespace vasily
