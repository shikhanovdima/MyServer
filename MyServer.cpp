#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include "MyServer.h"

MyServer::MyServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this); //инициализация сервера
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyServer::slotNewConnection); //подключение сервера к слоту


    if(!mTcpServer->listen(QHostAddress::Any, 6666)){ //привязываем сервер к порту и ip-ку
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyServer::slotNewConnection() { //как только приходит сигнал, вызывается слот "NewConnection"

    mTcpSocket = mTcpServer->nextPendingConnection(); //возвращаем сокет
    mTcpSocket->write("Hello, World!!! I am a server!\r\n");//и записываем в него данные которые потом пойдут к клиенту

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyServer::slotServerRead); //связываем сигналы со слотами
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyServer::slotClientDisconnected);

}
//принимает данные от клиента, пишет их в массив и отправляет их обратно
void MyServer::slotServerRead() {
    while(mTcpSocket->bytesAvailable()>0) { //Работаем пока идут данные от клиента
        QString str = mTcpSocket->readAll(); //Получаем данные от клиента
        QByteArray array; //заводим строку
        array.append(str);//записываем данные в строку
        mTcpSocket->write(array); //отправляем их клиенту
    }
}


void MyServer::slotClientDisconnected() {
    mTcpSocket->close(); //в случае отключения клиента закрываем соединение
}
