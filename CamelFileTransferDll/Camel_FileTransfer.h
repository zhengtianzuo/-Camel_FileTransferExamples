/*!
 *@file Camel_FileTransfer.h
 *@brief 文件传输开发组件定义
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author 郑天佐
 *@date 2013-4-3
*/
#pragma once
#include <string.h>

//!@brief 通讯消息
const int Cls_intSendCode_Heart                    = 0x00001000;                        //!<心跳包信息
const int Cls_intSendCode_HeartOutTime             = 0x00001001;                        //!<心跳包超时信息
const int Cls_intDataContentSize                   = 464;                               //!<数据大小

//!@struct 数据包结构
typedef struct tag_Cls_stuData
{
    tag_Cls_stuData()
    {
        Cls_intIPAdrs                              = 0;
        Cls_intPort                                = 0;
        Cls_intFunction                            = 0;
        Cls_intSign                                = 0;
        Cls_intIndex                               = 0;
        Cls_intSendTime                            = 0;
        Cls_intSendSize                            = 0;
        memset(Cls_chrData, 0, Cls_intDataContentSize);
    }

    int Cls_funGetIPAdrs() const
    {
        return (Cls_intIPAdrs);
    }

    void Cls_subSetIPAdrs(int intIPAdrs)
    {
        Cls_intIPAdrs = intIPAdrs;
    }

    int Cls_funGetPort() const
    {
        return (Cls_intPort);
    }

    void Cls_subSetPort(int intPort)
    {
        Cls_intPort = intPort;
    }

    int Cls_funGetFunction() const
    {
        return (Cls_intFunction);
    }

    void Cls_subSetFunction(int intFunction)
    {
        Cls_intFunction = intFunction;
    }

    int Cls_funGetSign() const
    {
        return (Cls_intSign);
    }

    void Cls_subSetSign(int intSign)
    {
        Cls_intSign = intSign;
    }

    int Cls_funGetIndex() const
    {
        return (Cls_intIndex);
    }

    void Cls_subSetIndex(int intIndex)
    {
        Cls_intIndex = intIndex;
    }

    int Cls_funGetSendTime() const
    {
        return (Cls_intSendTime);
    }

    void Cls_subSetSendTime(int intSendTime)
    {
        Cls_intSendTime = intSendTime;
    }

    int Cls_funGetSendSize() const
    {
        return (Cls_intSendSize);
    }

    void Cls_subSetSendSize(int intSendSize)
    {
        Cls_intSendSize = intSendSize;
    }

private:
    int Cls_intIPAdrs;                                                                  //!<数据地址
    int Cls_intPort;                                                                    //!<数据端口
    int Cls_intFunction;                                                                //!<功能代码
    int Cls_intSign;                                                                    //!<发送标志
    int Cls_intIndex;                                                                   //!<组包序号
    int Cls_intSendTime;                                                                //!<发送时间
    int Cls_intSendSize;                                                                //!<内容长度

public:
    char Cls_chrData[Cls_intDataContentSize];                                           //!<具体内容
} Cls_stuData, *Cls_lpstuData;
const int Cls_intDataTotalSize                     = sizeof(Cls_stuData);               //!<消息内容长度  = 488

//!@struct 数据包结构
typedef struct tag_Cls_stuDataPkg
{
    tag_Cls_stuDataPkg()
    {
        Cls_subInit();
    }

    void Cls_subInit()
    {
        Cls_chrPSendData = NULL;
        Cls_lpfunTransfer = NULL;
        Cls_lpUserData = NULL;
        memset(&Cls_Data, 0, Cls_intDataTotalSize);
    }

    char *&Cls_funGetPSendData()
    {
        return (Cls_chrPSendData);
    }

    void Cls_subSetPSendData(char* chrPSendData)
    {
        Cls_chrPSendData = chrPSendData;
    }

    void *&Cls_funGetfunTransfer()
    {
        return (Cls_lpfunTransfer);
    }

    void Cls_subSetfunTransfer(void *lpfunTransfer)
    {
        Cls_lpfunTransfer = lpfunTransfer;
    }

    void *&Cls_funGetUserData()
    {
        return (Cls_lpUserData);
    }

    void Cls_subSetUserData(void *lpUserData)
    {
        Cls_lpUserData = lpUserData;
    }

    Cls_stuData Cls_Data;                                                               //!<结构内容

private:
    char *Cls_chrPSendData;                                                             //!<内容指针
    void *Cls_lpfunTransfer;                                                            //!<传输指针
    void *Cls_lpUserData;                                                               //!<用户数据
} Cls_stuDataPkg, *Cls_lpstuDataPkg;
const int Cls_intDataPkgTotalSize = sizeof(Cls_stuDataPkg);                             //!<消息内容长度

//!@struct 心跳包发送结构
typedef struct tag_Cls_stuPackageSendHeart
{
    int Cls_intUserID;                                                                  //!<用户ID
    int Cls_intUserType;                                                                //!<用户类型
} Cls_stuPackageSendHeart, *Cls_lpstuPackageSendHeart;

//!@struct 心跳包接收结构
typedef struct tag_Cls_stuPackageRcvHeart
{
    tag_Cls_stuPackageRcvHeart()
    {
        Cls_subInit();
    }

    void Cls_subInit()
    {
        Cls_intUserID = 0;
        Cls_intIPAdrs = 0;
        Cls_intPort = 0;
        Cls_intUserType = 0;
        Cls_intSendTime = 0;
        memset(&stuSendHeart, 0, sizeof(Cls_stuPackageSendHeart));
    }

    int Cls_funGetUserID() const
    {
        return (Cls_intUserID);
    }

    void Cls_subSetUserID(int intUserID)
    {
        Cls_intUserID = intUserID;
    }

    int Cls_funGetIPAdrs() const
    {
        return (Cls_intIPAdrs);
    }

    void Cls_subSetIPAdrs(int intIPAdrs)
    {
        Cls_intIPAdrs = intIPAdrs;
    }

    int Cls_funGetPort() const
    {
        return (Cls_intPort);
    }

    void Cls_subSetPort(int intPort)
    {
        Cls_intPort = intPort;
    }

    int Cls_funGetUserType() const
    {
        return (Cls_intUserType);
    }

    void Cls_subSetUserType(int intUserType)
    {
        Cls_intUserType = intUserType;
    }

    int Cls_funGetSendTime() const
    {
        return (Cls_intSendTime);
    }

    void Cls_subSetSendTime(int intSendTime)
    {
        Cls_intSendTime = intSendTime;
    }

    Cls_stuPackageSendHeart stuSendHeart;                                               //!<具体内容

private:
    int Cls_intUserID;                                                                  //!<用户ID
    int Cls_intIPAdrs;                                                                  //!<数据地址
    int Cls_intPort;                                                                    //!<数据端口
    int Cls_intUserType;                                                                //!<用户类型
    int Cls_intSendTime;                                                                //!<发送时间
} Cls_stuPackageRcvHeart, *Cls_lpstuPackageRcvHeart;

//!@brief 数据通讯类型
const int Cls_intSign_NoSign                       =          0x00000000;               //!<无消息
const int Cls_intSign_WaitDo                       =          0x00000001;               //!<待处理
const int Cls_intSign_Doing                        =          0x00000002;               //!<处理中
const int Cls_intSign_Response                     =          0x00000003;               //!<回应消息
const int Cls_intSign_Heart                        =          0x00000004;               //!<心跳包

//!@brief 数据通讯状态
const int Cls_intSendStatus_NoSign                 =          0x00000000;               //!<空闲
const int Cls_intSendStatus_Normal                 =          0x00000001;               //!<正常传输中
const int Cls_intSendStatus_Retrying               =          0x00000002;               //!<数据重发中
const int Cls_intSendStatus_Faild                  =          0x00000003;               //!<数据发送失败

//!@brief 返回错误码分析
const int clsFileTransfer_intErrorCode_Success     =           0x00000001;              //!<正确的值
const int clsFileTransfer_intErrorCode_NoRights    =           0x00000002;              //!<效验未通过
const int clsFileTransfer_intErrorCode_Socket      =           0x0000000D;              //!<套接字错误
const int clsFileTransfer_intErrorCode_ThreadW     =           0x00000021;              //!<线程失败
const int clsFileTransfer_intErrorCode_Handle      =           0x00000022;              //!<创建句柄失败
const int clsFileTransfer_intErrorCode_OutOfCache  =           0x00000023;              //!<超出缓冲最大值
const int clsFileTransfer_intErrorCode_OutOfMemory =           0x00000024;              //!<内存溢出
const int clsFileTransfer_intErrorCode_OutTime     =           0x00000025;              //!<操作超时
const int clsFileTransfer_intErrorCode_UserR       =           0x00000098;              //!<对方决绝接收文件
const int clsFileTransfer_intErrorCode_UserExit    =           0x00000099;              //!<自行退出

//!@brief 数据队列返回错误码分析
const int clsDataQueue_intErrorCode_Success        =           0x00000001;              //!<正确的值
const int clsDataQueue_intErrorCode_InvalidValue   =           0x00000002;              //!<无效的值
const int clsDataQueue_intErrorCode_OutOfCache     =           0x00000003;              //!<超出缓冲
const int clsDataQueue_intErrorCode_OutOfMemory    =           0x00000004;              //!<内存溢出
const int clsDataQueue_intErrorCode_NoData         =           0x00000005;              //!<无数据

//!@brief 回调函数
typedef unsigned(*Cls_lpfunTransferCallBack)(const void *pContext, const Cls_lpstuDataPkg pData);
