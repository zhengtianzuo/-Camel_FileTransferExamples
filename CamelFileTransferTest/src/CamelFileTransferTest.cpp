
// *@file CamelFileTransferTest.cpp
// *@brief CamelFileTransferTest
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include "CamelFileTransferTest.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QFile>
#include <QTime>

CamelFileTransferTest::CamelFileTransferTest() :
    m_pFileTransferInterface(nullptr),
    m_pFileTransfer(nullptr),
    m_pDataQueueInterface(nullptr),
    m_pDataQueueRecv(nullptr),
    m_pThreadFileRecv(nullptr),
    m_pThreadFileSend(nullptr) {
}

CamelFileTransferTest::~CamelFileTransferTest() {
    m_pThreadFileRecv->terminate();
    delete m_pThreadFileRecv;
    m_pThreadFileSend->terminate();
    delete m_pThreadFileSend;
    m_pDataQueueInterface->Cls_funTerminate(m_pDataQueueRecv);
    delete m_pDataQueueInterface;
    m_pFileTransferInterface->Cls_funTerminate(m_pFileTransfer);
    delete m_pFileTransferInterface;
}

void CamelFileTransferTest::init() {
    m_pFileTransferInterface = new Camel_FileTransferInterface;
    m_pFileTransfer = m_pFileTransferInterface->Cls_funInitialize();
    m_pDataQueueInterface = new Camel_DataQueueInterface;
    m_pDataQueueRecv = m_pDataQueueInterface->Cls_funInitialize();
    int intPort = 6666;
    int intError = m_pFileTransfer->Cls_funTransferInitialize(
                       nullptr, intPort, reinterpret_cast<void *>(Sub_funMsgRcv),
                       m_pDataQueueRecv, 6000, false);
    if (intError != clsFileTransfer_intErrorCode_Success) {
        return;
    }
    Cls_stuParam stuParam(0, 5168, 1024, 2280, 3, 5, 600);
    m_pFileTransfer->Cls_funTransferSetParam(&stuParam);

    m_pThreadFileRecv = new CThreadFileRecv();
    m_pThreadFileSend = new CThreadFileSend();
    connect(m_pThreadFileRecv, &CThreadFileRecv::sSetIPList, this, &CamelFileTransferTest::sSetIPList);
    connect(m_pThreadFileSend, &CThreadFileSend::sSetProgressMax, this, &CamelFileTransferTest::sSetProgressMax);
    connect(m_pThreadFileSend, &CThreadFileSend::sSetProgressValue, this, &CamelFileTransferTest::sSetProgressValue);
    connect(m_pThreadFileSend, &CThreadFileSend::sSetProgressSpeed, this, &CamelFileTransferTest::sSetProgressSpeed);
    m_pThreadFileRecv->init(m_pDataQueueRecv);
    m_pThreadFileRecv->start();
}

void CamelFileTransferTest::cls_subSendFile(QString strFileName, QString strIP, QString strPort) {
    QString sFileName = strFileName.replace("file:///", "");
    QFile file(sFileName);
    if (!file.exists()) {
        return;
    }
    int nIP = ntohl(inet_addr(strIP.toStdString().c_str()));
    int nPort = atoi(strPort.toStdString().c_str());
    m_pThreadFileSend->init(m_pFileTransfer, sFileName, nIP, nPort);
    m_pThreadFileSend->start();
}

void CamelFileTransferTest::Sub_funMsgRcv(void *pContext, Cls_lpstuDataPkg lpstuData) {
    Cls_stuDataPkg stuDataNew;
    memcpy(&stuDataNew, lpstuData, sizeof(Cls_stuDataPkg));
    int intSendSize = lpstuData->Cls_Data.Cls_funGetSendSize();
    if (intSendSize > Cls_intDataContentSize) {
        char *chrPSendData = new char[static_cast<unsigned int>(intSendSize)];
        memcpy(chrPSendData, lpstuData->Cls_funGetPSendData(), static_cast<unsigned int>(intSendSize));
        stuDataNew.Cls_subSetPSendData(chrPSendData);
    } else {
        stuDataNew.Cls_subSetPSendData(stuDataNew.Cls_Data.Cls_chrData);
    }
    CCamel_DataQueue *const dataQueue = reinterpret_cast<CCamel_DataQueue *>(pContext);
    dataQueue->Cls_funQueuePushBack(&stuDataNew);
}

void CThreadFileRecv::init(CCamel_DataQueue *pDataQueueRecv) {
    m_pDataQueueRecv = pDataQueueRecv;
#ifdef Q_OS_WIN32
    m_strFileName = "rcv.data";
#endif
#ifdef Q_OS_LINUX
    m_strFileName = "/home/zhengtianzuo/rcv.data";
#endif
#ifdef Q_OS_ANDROID
    m_strFileName = "/sdcard/rcv.data";
#endif
#ifdef Q_OS_OSX
    m_strFileName = "/Users/zhengtianzuo/rcv.data";
#endif
    getLocalIP();
}

void CThreadFileRecv::run() {
    Cls_stuDataPkg stuRcvMsgCache;
    FILE *fp = fopen(m_strFileName.toStdString().c_str(), "wb+");
    int intFileIndex = 0;
    int intFileLen = 0;

    while (1) {
        if (m_pDataQueueRecv->Cls_funQueuePopUp(&stuRcvMsgCache) != clsDataQueue_intErrorCode_Success) {
            msleep(200);
            continue;
        }

        if (stuRcvMsgCache.Cls_Data.Cls_funGetSendSize() <= Cls_intDataContentSize) {
            stuRcvMsgCache.Cls_subSetPSendData(stuRcvMsgCache.Cls_Data.Cls_chrData);
        }

        intFileLen = ((intFileIndex % 2) == 0) ? (intFileIndex / 2) * (Cls_nBigBufSize + Cls_nSmallBufSize) :
            static_cast<int>(ceil(static_cast<double>(intFileIndex) / 2) * (Cls_nBigBufSize + Cls_nSmallBufSize) - Cls_nSmallBufSize);
        intFileIndex++;

        fseek(fp, intFileLen, SEEK_SET);
        fwrite(stuRcvMsgCache.Cls_funGetPSendData(), 1, stuRcvMsgCache.Cls_Data.Cls_funGetSendSize(), fp);
        fflush(fp);

        if (stuRcvMsgCache.Cls_Data.Cls_funGetSendSize() > Cls_intDataContentSize) {
            delete stuRcvMsgCache.Cls_funGetPSendData();
        }
        if (intFileIndex == stuRcvMsgCache.Cls_Data.Cls_funGetFunction() + 1) break;
    }
    fclose(fp);
}

void CThreadFileRecv::getLocalIP() {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, list) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            if (address.toString().contains("127.0.")) continue;
            emit sSetIPList(address.toString());
        }
    }
}

void CThreadFileSend::init(Camel_FileTransferInt *pFileTransfer, QString strFileName, int nIP, int nPort) {
    m_strFileName = strFileName;
    m_nIP = nIP;
    m_nPort = nPort;
    m_pFileTransfer = pFileTransfer;
}

const float FileSize_KB = 1024.0;
const float FileSize_MB = (1024.0 * FileSize_KB);
const float FileSize_GB = (1024.0 * FileSize_MB);

QString CThreadFileSend::subByte2Str(unsigned long nByte) {
    QString strNum = "";
    double dblNum = 0.00;
    if (nByte > FileSize_GB) {
        dblNum = static_cast<double>(nByte/FileSize_GB);
        strNum.sprintf(("%0.2fGB"), dblNum);
    } else if (nByte > FileSize_MB) {
        dblNum = static_cast<double>(nByte/FileSize_MB);
        strNum.sprintf(("%0.2fMB"), dblNum);
    } else if (nByte > FileSize_KB) {
        dblNum = static_cast<double>(nByte/FileSize_KB);
        strNum.sprintf(("%0.2fKB"), dblNum);
    } else {
        strNum.sprintf(("%dByte"), nByte);
    }
    return(strNum);
}

void CThreadFileSend::subProgressSpeed(QTime startTime, long lngFileSizeMax) {
    int elapsed = startTime.msecsTo(QTime::currentTime());
    QString strSpeed = subByte2Str(lngFileSizeMax / (static_cast<float>(elapsed) / 1000)) + "/s";
    emit sSetProgressSpeed(subByte2Str(lngFileSizeMax), QString::number((static_cast<float>(elapsed) / 1000), 'f', 2) + "s", strSpeed);
}

void CThreadFileSend::run() {
    FILE *fp = fopen(m_strFileName.toLocal8Bit().toStdString().c_str(), "rb");
    fseek(fp, 0, SEEK_SET);
    fseek(fp, 0, SEEK_END);
    long lngFileSize = ftell(fp);
    long lngFileSizeMax = lngFileSize;
    fseek(fp, 0, SEEK_SET);
    int nMaxNum = lngFileSize / ((Cls_nBigBufSize + Cls_nSmallBufSize) / 2);
    emit sSetProgressMax(nMaxNum);
    emit sSetProgressValue(0);
    char chrData[Cls_nBigBufSize];
    int intSendBufSize = Cls_nBigBufSize;
    int intFileIndex = 0;
    QTime startTime = QTime::currentTime();

    while (lngFileSize > 0) {
        int ulgSize = fread(chrData, 1, intSendBufSize, fp);
        if (ulgSize == 0) break;
        if (lngFileSize < intSendBufSize) {
            ulgSize = lngFileSize;
        }
        Cls_stuSendParam stuSendParam(0, m_nIP, m_nPort, Cls_intSign_WaitDo, nMaxNum, chrData, ulgSize);
        int intErrorNo = m_pFileTransfer->Cls_funTransferMsg_Send(&stuSendParam);
        if (intErrorNo == clsFileTransfer_intErrorCode_Success) {
            intFileIndex++;
            sSetProgressValue(intFileIndex);
        }
        lngFileSize -= ulgSize;
        if ((intFileIndex % 2) == 0) {
            intSendBufSize = Cls_nBigBufSize;
        } else {
            intSendBufSize = Cls_nSmallBufSize;
        }
    }
    fclose(fp);
    subProgressSpeed(startTime, lngFileSizeMax);
}
