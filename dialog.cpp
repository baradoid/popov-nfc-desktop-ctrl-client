#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    bRecvd(0),
    settings("murinets", "popov-nfc")
{
    ui->setupUi(this);

    int port = settings.value("port", 3600).toInt();
    ui->lineEditPort->setText(QString::number(port));
    ui->lineEditPort->setValidator(new QIntValidator(0,65535, this));

    sock = new QTcpSocket(this);

    ui->progressBar->setValue(0);

    connect(sock, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));

}

Dialog::~Dialog()
{
    int port = ui->lineEditPort->text().toInt();
    settings.setValue("port", port);
    delete ui;
}

void Dialog::handleConnected()
{
    //qDebug("handleConnected");
    if(ui->pushButtonConnect->text()=="Connect"){
        ui->pushButtonConnect->setText("Disconnect");
    }
}

void Dialog::handleReadyRead()
{
    bRecvd += sock->bytesAvailable();
    QString str(sock->readAll());
    QStringList strParts = str.split(" ");

    ui->lineEditBytesRecvd->setText(QString::number(bRecvd));

    ui->lineEdit->setText(strParts[0]);
    int prog = strParts[1].toInt();
    ui->progressBar->setValue(prog);


    //qDebug() << qPrintable(">" + strParts[0] + " >"+ strParts[1]);
}

void Dialog::handleDisconnected()
{
    //qDebug("handleDisconnected");
    if(ui->pushButtonConnect->text()=="Disconnect"){
        ui->pushButtonConnect->setText("Connect");
    }
}

void Dialog::on_pushButtonConnect_clicked()
{
    if(ui->pushButtonConnect->text()=="Connect"){
        sock->connectToHost("127.0.0.1", 3600);
    }
    else if(ui->pushButtonConnect->text()=="Disconnect"){
        sock->close();
    }
}
