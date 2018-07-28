#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QSettings>
#include <stdint.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QTcpSocket *sock;
    uint32_t bRecvd;
    QSettings settings;
    //QSound *bells;

private slots:
    void handleConnected();
    void handleReadyRead();
    void handleDisconnected();
    void on_pushButtonConnect_clicked();
    void on_pushButtonShort_clicked();
    void on_pushButtonLong_clicked();
};

#endif // DIALOG_H
