#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


namespace vasily
{

/**
 * \brief Pretty simple imitator Fanuc M-20iA.
 */
class Server : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief            Constructor which initializes sockets and bindes ports to
     *                   them.
     * \param[in] port   Port for connection.
     * \param[in] parent The necessary data for Qt.
     */
    explicit		Server(const quint16 port, QObject* parent = nullptr);

    /**
     * \brief Default destructor.
     */
    virtual         ~Server() = default;

    /**
     * \brief           Deleted copy constructor.
     * \param[in] other Other client object.
     */
    Server(const Server& other) = delete;

    /**
     * \brief           Deleted copy assignment operator.
     * \param[in] other Other client object.
     * \return          Returns nothing because it's deleted.
     */
    Server&	operator=(const Server& other) = delete;

    /**
     * \brief            Deleted move constructor.
     * \param[out] other Other client object.
     */
    Server(Server&& other) = delete;

    /**
     * \brief            Deleted move assignment operator.
     * \param[out] other Other client object.
     * \return           Returns nothing because it's deleted.
     */
    Server&	operator=(Server&& other) = delete;

    /**
     * \brief Fuction processes sockets (call 'bind' and 'listen').
     */
    void			launch() const;


signals:


 private slots:
    /**
     * \brief Process new client connection to sending socket.
     */
    void slotNewConnection();

    /**
     * \brief Receive data from client
     */
    void slotReadFromClient() const;

    /**
     * \brief Process client disconnection from sending socket.
     */
    void slotClientDisconnected() const;


protected:
    /**
     * \brief Variable used to keep reciving port.
     */
    quint16                         _port;

    /**
     * \brief Connected socket used to receive data.
     */
    std::unique_ptr<QTcpServer>	    _socket;

    /**
     * \brief Pointer to socket used to work with clients.
     */
    QTcpSocket*                     _clientSocket;
};

} // namespace vasily

#endif // SERVER_H
