#include <iostream>

#include <QCoreApplication>

#include "Server.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Console server v 0.1\n\n";

    qDebug() << "Input server port:";
    quint16 serverPort;
    std::cin >> serverPort;

   	vasily::Server server(serverPort);
    server.launch();

    return a.exec();
}
