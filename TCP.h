#ifndef TCP_H
#define TCP_H
#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QByteArray>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>

class TCP : public QThread
{
    Q_OBJECT
public:
    explicit TCP(QObject *parent = nullptr);

    bool connect(QString ip, quint16 port);
    void disconnect();
    void transmit(QString transData);
    bool stateConnect();

signals:
    void response(QList<QByteArray>);
    void errorConnect(QString, const Qt::GlobalColor);
    void timeout(QString, const Qt::GlobalColor);

private slots:
    void receive();

protected:
    void run();
private:
    bool TCPConnect = false;
    QList<QByteArray> resMessBuff;
    QTcpSocket socket;
    QByteArray dataRX;
};
#endif // TCP_H
