#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR += $$PWD/../../bin/mac/debug
} else {
    DESTDIR += $$PWD/../../bin/mac/release
}

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../../CamelFileTransferDll/mac/Debug -lCamel_FileTransfer -L$$PWD
} else {
    LIBS += -L$$PWD/../../../CamelFileTransferDll/mac/Release -lCamel_FileTransfer -L$$PWD
}

include($$PWD/../CamelFileTransferTest.pri)
