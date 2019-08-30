
// *@file CamelFileTransferTest.h
// *@brief CamelFileTransferTest
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#pragma once
#include <QObject>
#include <QVector>
#include <QThread>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif
#ifdef Q_OS_LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#ifdef Q_OS_MAC
#include <arpa/inet.h>
#endif
#include "../../CamelFileTransferDll/Camel_FileTransfer.h"
#include "../../CamelFileTransferDll/Camel_FileTransferInterface.h"

const int Cls_nBigBufSize = 10236;
const int Cls_nSmallBufSize = 400;

class CThreadFileSend : public QThread {
    Q_OBJECT

 public:
    void init(Camel_FileTransferInt *pFileTransfer, QString strFileName, int nIP, int nPort);

 protected:
    void run();

 signals:
    void sSetProgressMax(int nMax);
    void sSetProgressValue(int nValue);
    void sSetProgressSpeed(QString strFileSize, QString strTotalTime, QString strSpeed);

 private:
    QString subByte2Str(unsigned long nByte);
    void subProgressSpeed(QTime startTime, long lngFileSizeMax);

    Camel_FileTransferInt *m_pFileTransfer;
    QString m_strFileName;
    int m_nIP;
    int m_nPort;
};

class CThreadFileRecv : public QThread {
    Q_OBJECT

 public:
    void init(CCamel_DataQueue* pDataQueueRecv);

 protected:
    void run();

 signals:
    void sSetIPList(QString strText);

 private:
    CCamel_DataQueue* m_pDataQueueRecv;
    QString m_strFileName;

    void getLocalIP();
};

class CamelFileTransferTest : public QObject {
    Q_OBJECT

 public:
    CamelFileTransferTest();
    ~CamelFileTransferTest();

    void init();
    Q_INVOKABLE void cls_subSendFile(QString strFileName, QString strIP, QString strPort);

 signals:
    void sSetIPList(QString strText);
    void sSetProgressMax(int nMax);
    void sSetProgressValue(int nValue);
    void sSetProgressSpeed(QString strFileSize, QString strTotalTime, QString strSpeed);

 private:
    Camel_FileTransferInterface *m_pFileTransferInterface;
    Camel_FileTransferInt *m_pFileTransfer;
    Camel_DataQueueInterface *m_pDataQueueInterface;
    CCamel_DataQueue* m_pDataQueueRecv;
    CThreadFileRecv* m_pThreadFileRecv;
    CThreadFileSend* m_pThreadFileSend;

    static void Sub_funMsgRcv(void *pContext, Cls_lpstuDataPkg lpstuData);
    static void Sub_funMsgRcvA(void *pParam);
};
