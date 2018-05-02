#include <iostream>
#include <string>

#include <QCoreApplication>

#include "Client.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Console client for connecting to Server v 0.1\n\n";

    constexpr quint16 kServerPort = 9999;

    qDebug() << "Input server IP:";
    std::string serverIP;
    std::cin >> serverIP;

    vasily::Client client(kServerPort, serverIP);
    client.launch();
    client.run();

    return a.exec();
}
