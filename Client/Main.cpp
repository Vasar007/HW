#include <iostream>
#include <string>

#include <QCoreApplication>

#include "Client.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Console client for connecting to Server v 0.1\n\n";

    qDebug() << "Input server port:";
    quint16 serverPort;
    std::cin >> serverPort;

    qDebug() << "Input server IP:";
    std::string serverIP;
    std::cin >> serverIP;

    vasily::Client client(serverPort, serverIP);
    client.launch();
    client.run();

    return a.exec();
}
