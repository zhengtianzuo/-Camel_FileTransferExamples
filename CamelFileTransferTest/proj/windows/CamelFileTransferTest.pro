#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR += $$PWD/../../bin/windows/debug
} else {
    DESTDIR += $$PWD/../../bin/windows/release
}

CONFIG(debug, debug|release) {
    LIBS += -lws2_32 -L$$PWD/../../../CamelFileTransferDll/windows/Debug -lCamel_FileTransfer -L$$PWD
} else {
    LIBS += -lws2_32 -L$$PWD/../../../CamelFileTransferDll/windows/Release -lCamel_FileTransfer -L$$PWD
}

include($$PWD/../CamelFileTransferTest.pri)
