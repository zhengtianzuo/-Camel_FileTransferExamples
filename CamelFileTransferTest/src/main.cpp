
// *@file main.cpp
// *@brief 程序主文件
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CamelFileTransferTest.h"

// #include "vld.h"
// #pragma comment(lib, "vld.lib")

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CamelFileTransferTest ftTest;
    engine.rootContext()->setContextProperty("ftTest", &ftTest);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    ftTest.init();
    return app.exec();
}
