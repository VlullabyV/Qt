#ifndef EX1_H
#define EX1_H

#include <QMainWindow>
#include<QtNetwork>
namespace Ui {
class ex1;
}
//wasdasd
class ex1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ex1(QWidget *parent = 0);
    ~ex1();

    //

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void processPendingDatagram();
    void on_pushButton_3_clicked();
    QString getLocalIp();
    void on_pushButton_4_clicked();
    void rec();

private:
    Ui::ex1 *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    QString *temp;
    quint16 *sendPort;
    quint16 *receivePort;
    QUdpSocket *SG;//组播
    QUdpSocket *RG;//组播接收，

};
#endif // EX1_H
