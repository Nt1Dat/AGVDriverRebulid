#include "TCP.h"

TCP::TCP(QObject *parent) : QThread{parent} {

}

bool TCP::connect(QString ip, quint16 port) {
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(receive()));
    socket.connectToHost(QHostAddress(ip), port);


  if (socket.waitForConnected()) {
      if (!isRunning())
      {   start();
      }
      TCPConnect = true;
      qDebug()<<"bugg";

    return 0;
  } else {
    emit errorConnect(tr("Can't connect to %1:%2, error code %3")
                          .arg(ip)
                          .arg(port)
                          .arg(socket.error()),
                      Qt::red);
    return 1;
  }
}

void TCP::disconnect() {
  terminate();
  socket.close();
}

void TCP::transmit(QList<QString> transData) {
  QString mess = transData.join(' ');
  socket.write(mess.toUtf8());
}

bool TCP::stateConnect() { return TCPConnect; }

void TCP::receive() {
  QByteArray dataRX_ba = socket.readAll();
  qDebug()<<dataRX_ba;
  QList<QByteArray> buff;
  // Loại bỏ ký tự đầu (0) và cuối (\n)
  if (dataRX_ba.startsWith("0 ") && dataRX_ba.endsWith(",")) {
    // Loại bỏ ký tự đầu (0) và cuối (\n)
    dataRX_ba = dataRX_ba.mid(2, dataRX_ba.length() - 3);
    // Tách giá trị A1 đến A6 bằng dấu phẩy và lưu vào danh sách buff
     buff = dataRX_ba.split(',');
    qDebug()<<buff;
    // Kiểm tra xem có đúng 6 giá trị trong danh sách
    if (buff.size() == 6) {
         emit response(buff);
    } else {
        qDebug() << "Not have 6 value";
    }
  } else {
    qDebug() << "Error on begin or end";
    qDebug()<<dataRX_ba;
  }

}

void TCP::run() {

}
