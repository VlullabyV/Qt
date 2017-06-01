#include "ex1.h"
#include "ui_ex1.h"
#include<QtNetwork>
#include<QDebug>
#include<QThread>
ex1::ex1(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ex1)
{   
    RG=new QUdpSocket(this);
    RG->bind(QHostAddress::AnyIPv4,62224,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    RG->joinMulticastGroup(QHostAddress("224.2.2.2"));
    connect(RG,SIGNAL(readyRead()),this,SLOT(rec()));
    ui->setupUi(this);
}

ex1::~ex1()
{
    delete ui;
}
void ex1::on_pushButton_clicked()
{
        ui->textBrowser->append(ui->lineEdit_2->text());
        sender = new QUdpSocket(this);
        QByteArray datagram=(ui->lineEdit_2->text()).toUtf8().data();
        sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress((*temp)),(*sendPort));
        delete sender;
}
void ex1::on_pushButton_2_clicked()
{
  temp=new QString(ui->lineEdit->text());
  sendPort=new quint16(ui->lineEdit_3->text().toUInt());
  receivePort=new quint16(ui->lineEdit_4->text().toUInt());
}

void ex1::processPendingDatagram() //处理等待的数据报
{
    while(receiver->hasPendingDatagrams())  //拥有等待的数据报
    {
        QByteArray datagram; //拥于存放接收的数据报
        datagram.resize(receiver->pendingDatagramSize());
        //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        receiver->readDatagram(datagram.data(),datagram.size());
        QString *string;

        string=new QString(datagram);
        ui->textBrowser->append(*string);
    }
}
void ex1::rec(){
    while(RG->hasPendingDatagrams())  //拥有等待的数据报
    {
        QByteArray datagram; //拥于存放接收的数据报
        datagram.resize(RG->pendingDatagramSize());
        //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        RG->readDatagram(datagram.data(),datagram.size());
        QString *string;
        string=new QString(datagram);
        ui->textBrowser->append(*string);
    }
}

QString ex1::getLocalIp()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    QString localIp;
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            localIp = address.toString();
        }
    }
    return localIp;
}
void ex1::on_pushButton_3_clicked()
{
    receivePort=new quint16(ui->lineEdit_4->text().toUInt());
    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress::LocalHost,(*receivePort),QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
}

void ex1::on_pushButton_4_clicked()
{
  SG=new QUdpSocket(this);
      QByteArray content=ui->lineEdit_5->text().toUtf8().data();
      SG->writeDatagram(content.data(),content.size(),QHostAddress("224.2.2.2"),62224);
}
