#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QSettings>

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

private slots:
    void handleConnected();
    void handleReadyRead();
    void handleDisconnected();
    void on_pushButtonConnect_clicked();
};

#endif // DIALOG_H
