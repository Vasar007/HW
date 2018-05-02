#include <QCoreApplication>

#include "Server.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Console server v 0.1\n\n";

    constexpr quint16 kServerPort = 9999;
    vasily::Server server(kServerPort);
    server.launch();

    return a.exec();
}
