/*!
 *@file Camel_FileTransferInterface.h
 *@brief 文件传输开发组件接口
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author 郑天佐
 *@date 2013-4-3
*/
#pragma once

//!@brief 导出函数定义
#undef Camel_FileTransfer_LIB
#if defined (WIN32)
#define Camel_FileTransfer_ATR
#if defined (Camel_FileTransfer_dllexport)
#define Camel_FileTransfer_LIB _declspec(dllexport)
#else
#define Camel_FileTransfer_LIB _declspec(dllimport)
#endif
#else
#define Camel_FileTransfer_ATR __attribute__((visibility("default")))
#define Camel_FileTransfer_LIB
#endif

//!@brief 参数类型定义
typedef struct tag_Cls_stuParam
{
    tag_Cls_stuParam()
    {
        intSenderIndex = 0;
        intBaseServerPort = 0;
        intMsgInitSize = 0;
        intRcvExDataMax = 0;
        intRetryMax = 0;
        intRetryAllNo = 0;
        intInitRetryTime = 0;
    }

    tag_Cls_stuParam(
        int nSenderIndex,
        int nBaseServerPort,
        int nMsgInitSize,
        int nRcvExDataMax,
        int nRetryMax,
        int nRetryAllNo,
        int nInitRetryTime)
    {
        intSenderIndex = nSenderIndex;
        intBaseServerPort = nBaseServerPort;
        intMsgInitSize = nMsgInitSize;
        intRcvExDataMax = nRcvExDataMax;
        intRetryMax = nRetryMax;
        intRetryAllNo = nRetryAllNo;
        intInitRetryTime = nInitRetryTime;
    }

    int Cls_funGetSenderIndex() const
    {
        return (intSenderIndex);
    }

    void Cls_subSetSenderIndex(int nSenderIndex)
    {
        intSenderIndex = nSenderIndex;
    }

    int Cls_funGetBaseServerPort() const
    {
        return (intBaseServerPort);
    }

    void Cls_subSetBaseServerPort(int nBaseServerPort)
    {
        intBaseServerPort = nBaseServerPort;
    }

    int Cls_funGetMsgInitSize() const
    {
        return (intMsgInitSize);
    }

    void Cls_subSetMsgInitSize(int nMsgInitSize)
    {
        intMsgInitSize = nMsgInitSize;
    }

    int Cls_funGetRcvExDataMax() const
    {
        return (intRcvExDataMax);
    }

    void Cls_subSetRcvExDataMax(int nRcvExDataMax)
    {
        intRcvExDataMax = nRcvExDataMax;
    }

    int Cls_funGetRetryMax() const
    {
        return (intRetryMax);
    }

    void Cls_subSetRetryMax(int nRetryMax)
    {
        intRetryMax = nRetryMax;
    }

    int Cls_funGetRetryAllNo() const
    {
        return (intRetryAllNo);
    }

    void Cls_subSetRetryAllNo(int nRetryAllNo)
    {
        intRetryAllNo = nRetryAllNo;
    }

    int Cls_funGetInitRetryTime() const
    {
        return (intInitRetryTime);
    }

    void Cls_subSetInitRetryTime(int nInitRetryTime)
    {
        intInitRetryTime = nInitRetryTime;
    }

private:
    int intSenderIndex;
    int intBaseServerPort;
    int intMsgInitSize;
    int intRcvExDataMax;
    int intRetryMax;
    int intRetryAllNo;
    int intInitRetryTime;
} Cls_stuParam, *Cls_lpstuParam;

typedef struct tag_Cls_stuSendParam
{
    tag_Cls_stuSendParam()
    {
        intSenderIndex = 0;
        intIP = 0;
        intPort = 0;
        intSign = 0;
        intFunction = 0;
        chrPSendData = NULL;
        intSendSize = 0;
    }

    tag_Cls_stuSendParam(int nSenderIndex, int nIP, int nPort, int nSign,
                         int nFunction, char *cPSendData, int nSendSize)
    {
        intSenderIndex = nSenderIndex;
        intIP = nIP;
        intPort = nPort;
        intSign = nSign;
        intFunction = nFunction;
        chrPSendData = cPSendData;
        intSendSize = nSendSize;
    }

    int Cls_funGetSenderIndex() const
    {
        return (intSenderIndex);
    }

    void Cls_subSetSenderIndex(int nSenderIndex)
    {
        intSenderIndex = nSenderIndex;
    }

    int Cls_funGetIP() const
    {
        return (intIP);
    }

    void Cls_subSetIP(int nIP)
    {
        intIP = nIP;
    }

    int Cls_funGetPort() const
    {
        return (intPort);
    }

    void Cls_subSetPort(int nPort)
    {
        intPort = nPort;
    }

    int Cls_funGetSign() const
    {
        return (intSign);
    }

    void Cls_subSetSign(int nSign)
    {
        intSign = nSign;
    }

    int Cls_funGetFunction() const
    {
        return (intFunction);
    }

    void Cls_subSetFunction(int nFunction)
    {
        intFunction = nFunction;
    }

    char *Cls_funGetPSendData() const
    {
        return (chrPSendData);
    }

    void Cls_subSetPSendData(char * cPSendData)
    {
        chrPSendData = cPSendData;
    }

    int Cls_funGetSendSize() const
    {
        return (intSendSize);
    }

    void Cls_subSetSendSize(int nSendSize)
    {
        intSendSize = nSendSize;
    }

private:
    int intSenderIndex;
    int intIP;
    int intPort;
    int intSign;
    int intFunction;
    char *chrPSendData;
    int intSendSize;
} Cls_stuSendParam, *Cls_lpstuSendParam;

//!@class 文件传输模块类
class Camel_FileTransfer_LIB Camel_FileTransferInt
{
public:
    Camel_FileTransferInt() {};
    virtual ~Camel_FileTransferInt() {};

    /*!
    *@name Cls_funTransferSetParam
    *@brief 预设参数
    *@param[in] intBaseServerPort 初始绑定端口 = 5168
    *@param[in] intMsgInitSize 初始缓冲队列大小 = 16
    *@param[in] intRcvExDataMax 初始扩展接收内存池大小 = 2280
    *@param[in] intRetryMax 初始丢包重试最大数 = 3
    *@param[in] intRetryAllNo 初始重试时间倍数 = 5
    *@param[in] intInitRetryTime 初始重试时间(毫秒) = 600
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual int Cls_funTransferSetParam(Cls_lpstuParam lpstuParam) = 0;

    /*!
    *@name Cls_funTransferInitialize
    *@brief 组件初始化
    *@param[in] chrIPAddr 绑定IP地址
    *@param[in] intLocalPort 绑定端口号
    *@param[in] pCallback 回调指针
    *@param[in] pContext 回调上下文
    *@param[in] intHeartCheck 心跳包检测时间间隔
    *@param[in] bolHasLogTrace 是否有运行调试信息
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferInitialize(
        const char *chrIPAddr, int &intLocalPort,
        const void *pCallback, const void *pContext, int const intHeartCheck,
        bool bolHasLogTrace
#ifdef WIN32
        , void * hIOCP = nullptr
#endif
    ) = 0;

    /*!
    *@name Cls_funTransferTerminate
    *@brief 组件销毁
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferTerminate() = 0;

    /*!
        *@name Cls_funTransferAddSender
        *@brief 添加发送者
        *@param[in] intSign 发送标识
        *@return 无
        *@author 郑天佐
        *@date 2013-6-26
        */
    virtual int Cls_funTransferAddSender(
        int &intSenderIndex, int const intSign) = 0;

    /*!
    *@name Cls_funTransferMsg_BeginRcv
    *@brief 开始接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferMsg_BeginRcv() = 0;

    /*!
    *@name Cls_funTransferMsg_StopRcv
    *@brief 停止接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferMsg_StopRcv() = 0;

    /*!
    *@name Cls_funTransferMsg_DataFree
    *@brief 释放数据
    *@param[in] lpfunTransfer 类指针
    *@param[in] intDataIndex 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferMsg_DataFree(
        void *lpfunTransfer, int const intDataIndex) const = 0;

    /*!
    *@name Cls_funTransferMsg_Send
    *@brief 发送数据
    *@param[in] intIP IP地址
    *@param[in] intPort 端口
    *@param[in] intSign 数据标示
    *@param[in] intFunction 命令字
    *@param[in] chrPSendData 待发送数据指针
    *@param[in] intSendSize 待发送数据大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferMsg_Send(Cls_lpstuSendParam lpstuSendParam) = 0;

    /*!
    *@name Cls_funTransferGetStatus
    *@brief 获取状态
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferGetStatus() const = 0;

    /*!
    *@name Cls_funTransferGetType
    *@brief 获取类型
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferGetType() = 0;

    /*!
    *@name Cls_funTransferHeart_New
    *@brief 新建心跳包检测
    *@param[in] intRcvTime 判断接收时间
    *@param[in] intRcvID 接收ID
    *@param[in] lngRcvIPAdrs 接收IP地址
    *@param[in] intRcvPort 接收端口
    *@param[in] intRcvClientType 接收类型
    *@param[in] intSendID 发送ID
    *@param[in] intSendClientType 发送类型
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferHeart_New(
        int const intRcvTime, int const intRcvID,
        int const lngRcvIPAdrs, int const intRcvPort, int const intRcvClientType,
        int const intSendID, int const intSendClientType) = 0;

    /*!
    *@name Cls_funTransferHeart_Modify
    *@brief 修改心跳包检测
    *@param[in] intDataID 数据ID
    *@param[in] intIP IP地址
    *@param[in] intPort 端口
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferHeart_Modify(
        int const intDataID, int const intIP, int const intPort) = 0;

    /*!
    *@name Cls_funTransferHeart_Update
    *@brief 更新心跳包检测
    *@param[in] intDataID 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferHeart_Update(int const intDataID) = 0;

    /*!
    *@name Cls_funTransferHeart_Kill
    *@brief 删除心跳包检测
    *@param[in] intDataID 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funTransferHeart_Kill(int const intDataID) = 0;
};

//!@class 文件传输接口类
class Camel_FileTransfer_LIB Camel_FileTransferInterface
{
public:
    /*!
    *@name Camel_FileTransferInterface
    *@brief 构造函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    Camel_FileTransferInterface();

    /*!
    *@name ~Camel_FileTransferInterface
    *@brief 析构函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual ~Camel_FileTransferInterface();

    /*!
    *@name Cls_funInitialize
    *@brief 组件接口初始化
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static Camel_FileTransferInt *Cls_funInitialize();

    /*!
    *@name Cls_funTerminate
    *@brief 组件接口销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static void Cls_funTerminate(Camel_FileTransferInt *&pFileTransfer);
};

//!@class 数据队列模块类
class Camel_FileTransfer_LIB CCamel_DataQueue
{
public:
    CCamel_DataQueue() {};
    virtual ~CCamel_DataQueue() {};

    /*!
    *@name Cls_funQueueInitialize
    *@brief 队列初始化
    *@param[in] intMaxNo 队列初始大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueueInitialize(int const intMaxNo) = 0;

    /*!
    *@name Cls_funQueueTerminate
    *@brief 队列销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void Cls_funQueueTerminate() = 0;

    /*!
    *@name Cls_funQueuePushBack
    *@brief 数据入队列
    *@param[in] lpstuData 数据
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueuePushBack(const Cls_lpstuDataPkg lpstuData) = 0;

    /*!
    *@name Cls_funQueuePopUp
    *@brief 数据出队列
    *@param[in] lpstuData 数据
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueuePopUp(const Cls_lpstuDataPkg lpstuData) = 0;

    /*!
    *@name Cls_funQueueAllocPSendData
    *@brief 申请数据
    *@param[in] lpstuData 数据
    *@param[in] intSpaceSize 数据大小
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void Cls_funQueueAllocPSendData(
        Cls_lpstuDataPkg &lpstuData, int const intSpaceSize) = 0;

    /*!
    *@name Cls_funQueueFreePSendData
    *@brief 释放申请的数据
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void Cls_funQueueFreePSendData() = 0;

    /*!
    *@name Cls_funQueueGetUsedCount
    *@brief 获取已用队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueueGetUsedCount() const = 0;

    /*!
    *@name Cls_funQueueGetUnUseCount
    *@brief 获取未用队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueueGetUnUseCount() const = 0;

    /*!
    *@name Cls_funQueueGetAllCount
    *@brief 获取总队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funQueueGetAllCount() const = 0;

    /*!
    *@name Cls_funQueueClear
    *@brief 清理队列
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void Cls_funQueueClear() = 0;
};

//!@class 数据队列接口
class Camel_FileTransfer_LIB Camel_DataQueueInterface
{
public:
    /*!
    *@name Camel_DataQueueInterface
    *@brief 构造函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    Camel_DataQueueInterface();

    /*!
    *@name Camel_DataQueueInterface
    *@brief 析构函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual ~Camel_DataQueueInterface();

    /*!
    *@name Cls_funInitialize
    *@brief 数据队列初始化
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static CCamel_DataQueue *Cls_funInitialize();

    /*!
    *@name Cls_funTerminate
    *@brief 数据队列销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static void Cls_funTerminate(CCamel_DataQueue *&pDataQueue);
};

#undef Camel_FileTransfer_LIB
