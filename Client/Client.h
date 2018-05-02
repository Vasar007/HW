#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


namespace vasily
{

/**
 * \brief Typical implementation of client used for interaction with robot server.
 */
class Client : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief				 Constructor that initializes sockets and connects to server.
     * \param[in] serverPort Server port for connection.
     * \param[in] serverIP	 Server IP address for connection.
     * \param[in] parent     The necessary data for Qt.
     */
    explicit    Client(const quint16 serverPort, const std::string& serverIP,
                       QObject* parent = nullptr);

    /**
     * \brief Default destructor.
     */
    virtual     ~Client() = default;

    /**
     * \brief           Deleted copy constructor.
     * \param[in] other Other client object.
     */
                Client(const Client& other) = delete;

    /**
     * \brief           Deleted copy assignment operator.
     * \param[in] other Other client object.
     * \return          Returns nothing because it's deleted.
     */
    Client&     operator=(const Client& other) = delete;

    /**
     * \brief            Deleted move constructor.
     * \param[out] other Other client object.
     */
                Client(Client&& other) = delete;

    /**
     * \brief            Deleted move assignment operator.
     * \param[out] other Other client object.
     * \return           Returns nothing because it's deleted.
     */
    Client&	    operator=(Client&& other) = delete;

    /**
     * \brief Main method which starts infinite working loop.
     */
    void        run();

    /**
     * \brief Fuction processes sockets (call 'connect').
     */
    void        launch() const;


signals:
    /**
     * \brief          Notify client to send data to layer or server depend on work mode.
     * \param[in] data Data to be send.
     */
    void signalToSend(const QByteArray& data) const;


private slots:
    /**
     * \brief Receive data from server.
     */
    void slotReadFromServer() const;

    /**
     * \brief Process server disconnection from layer.
     */
    void slotServerDisconnected() const;

    /**
     * \brief          Send data to server after notifying from signal.
     * \param[in] data Data to be send.
     */
    void slotSendDataToServer(const QByteArray& data) const;


protected:
    /**
     * \brief Variable used to keep recieving server port.
     */
    quint16	                                           _serverPort;

    /**
     * \brief Connected to server socket used to receive data.
     */
    std::unique_ptr<QTcpSocket>                        _socket;

    /**
     * \brief Variable used to keep server IP address.
     */
    std::string                                        _serverIP;


    /**
     * \brief                        Establishe a connection to a specified socket.
     * \param[in] port               Port for connection.
     * \param[in] ip                 IP address for connection.
     * \param[out] socketToConnect   A descriptor identifying an unconnected socket.
     * \param[in] msecs              Time which Qt waits until the socket is connected. If this
     *                               parameter is -1, function will not time out.
     * \return                       If no error occurs, connect returns true, false otherwise.
     */
    bool        tryConnect(const quint16 port, const std::string& ip, QTcpSocket* socketToConnect,
                           const int msecs = 3000) const;

    /**
     * \brief Try to establish a connection to server again.
     */
    void        tryReconnect() const;

    /**
     * \brief          Send data on a connected socket.
     * \param[in] data A buffer containing the data to be transmitted.
     */
    void        sendData(const std::string& data) const;

    /**
     * \brief Main infinite working loop. Network logic to interacte with server are placed here.
     */
    void        waitLoop() const;
};

} // namespace vasily

#endif // CLIENT_H
