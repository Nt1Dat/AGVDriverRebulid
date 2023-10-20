#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_window();

     connect(&tcpThread, &TCP::response, this, &MainWindow::rxMessageThread);


}

void MainWindow::init_window()
{
    setFixedSize(width(), height());
    setWindowTitle("Movement Test via TCP");
    ui->btTrap->setDisabled(true);
    ui->btCmd->setDisabled(true);

    ui->btConnect->setText("Connect");
    ui->btConnect->setStyleSheet("QPushButton {color: green;}");

    ui->cbL->setChecked(true);
    ui->cbR->setChecked(true);

    QPen pen1;
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(3);
    pen1.setColor("#E2483E");

    QPen pen2;
    pen2.setStyle(Qt::SolidLine);
    pen2.setWidth(3);
    pen2.setColor("#5C97E3");

    QPen pen3;
    pen3.setStyle(Qt::SolidLine);
    pen3.setWidth(3);
    pen3.setColor("#5CE36E");

    // vel plot init
    ui->plVel->addGraph();
    ui->plVel->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plVel->graph(0)->setPen(pen1);
    ui->plVel->graph(0)->setName("Reference");

    ui->plVel->addGraph();
    ui->plVel->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->plVel->graph(1)->setPen(pen2);
    ui->plVel->graph(1)->setName("Velocity 1");

    ui->plVel->addGraph();
    ui->plVel->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->plVel->graph(2)->setPen(pen3);
    ui->plVel->graph(2)->setName("Velocity 2");

    plotSetting(ui->plVel, "Time", "Velocity");

    // pos plot init
    ui->plPos->addGraph();
    ui->plPos->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plPos->graph(0)->setPen(pen1);
    ui->plPos->graph(0)->setName("Reference");

    ui->plPos->addGraph();
    ui->plPos->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->plPos->graph(1)->setPen(pen2);
    ui->plPos->graph(1)->setName("Position 1");

    ui->plPos->addGraph();
    ui->plPos->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->plPos->graph(2)->setPen(pen3);
    ui->plPos->graph(2)->setName("Position 2");

    plotSetting(ui->plPos, "Time", "Position");
}

void MainWindow::plotSetting(QCustomPlot *plot, const char *xLabel,
                             const char *yLabel)
{
    QFont legendFont = font();
    legendFont.setPointSize(8);
    plot->yAxis->setLabel(yLabel);
    plot->xAxis->setLabel(xLabel);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->legend->setVisible(true);
    plot->legend->setFont(legendFont);
    plot->legend->setSelectedFont(legendFont);
    plot->legend->setSelectableParts(QCPLegend::spItems);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btConnect_clicked() {
    if (ui->btConnect->text() == "Connect")
    {
        if(!tcpThread.connect(ui->txtIP->text(),ui->txtPort->text().toInt()));
        {
            ui->btConnect->setText("Disconnect");
            ui->btConnect->setStyleSheet("QPushButton {color: red;}");
            ui->btTrap->setDisabled(false);
            ui->btCmd->setDisabled(false);
        }
    }
       else
        {
        tcpThread.disconnect();
            ui->btConnect->setText("Connect");
             ui->btConnect->setStyleSheet("QPushButton {color: green;}");
            ui->btTrap->setDisabled(true);
            ui->btCmd->setDisabled(true);
         }

}


void MainWindow::rxMessageThread(const QList<QByteArray> resMess)
{
         quint64 currentTime = time.elapsed() + preTime;
         timeBuff.append(currentTime);
         preTime = currentTime;
         time.start();

         velVal1Buff.append(resMess[0].toFloat());
         velVal2Buff.append(resMess[1].toFloat());
         velRefBuff.append(resMess[2].toFloat());
         posVal1Buff.append(resMess[3].toFloat());
         posVal2Buff.append(resMess[4].toFloat());
         posRefBuff.append(resMess[5].toFloat());

         qDebug()<<resMess[0].toFloat()<<","<< resMess[1].toFloat();

}



