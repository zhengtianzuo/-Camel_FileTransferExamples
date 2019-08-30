/*!
 *@file main.qml
 *@brief 主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0

ApplicationWindow {
    id: frmWindow
    visible: true
    width: 600
    height: 300
    title: qsTr("CamelFileTransferTest")

    Column{
        spacing: 12
        width: 560
        anchors.centerIn: parent

        Row{
            anchors.left: progressBar.left
            height: 32
            spacing: 6

            Text {
                text: qsTr("本机地址:")
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: ipList
                height: 32
                width: 150
                model: ListModel {
                    id: ipListModel
                }
            }
        }

        Row{
            anchors.left: progressBar.left
            height: 32
            spacing: 6

            Text {
                text: qsTr("远程地址:")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextInput{
                id: inputIP
                height: 32
                width: 150
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                text: "192.168.2.128"
                font.pixelSize: 14
                color: "#eeff0000"
                selectByMouse: true
            }

            Text {
                text: qsTr("远程端口:")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextInput{
                id: inputPort
                height: 32
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                text: "6666"
                font.pixelSize: 14
                color: "#eeff0000"
                selectByMouse: true
            }
        }

        ProgressBar {
            id: progressBar
            height: 24
            width: parent.width*0.8
            anchors.horizontalCenter: parent.horizontalCenter
            value: 0.0
            padding: 2

            background: Rectangle {
                implicitWidth: parent.width*0.8
                implicitHeight: 6
                color: "#e6e6e6"
                radius: 3
            }

            contentItem: Item {
                implicitWidth: parent.width*0.8
                implicitHeight: 4

                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height
                    radius: 2
                    color: "#17a81a"
                }
            }
        }

        TextEdit{
            height: 36
            width: parent.width*0.8
            anchors.horizontalCenter: parent.horizontalCenter
            text: fileDialog.file
            readOnly: true
            selectByKeyboard: true
            selectByMouse: true
            wrapMode: TextEdit.WordWrap
        }

        Row{
            height: 32
            width: parent.width*0.4
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 12

            Button{
                id: openBtn
                height: 32
                width: 80
                text: qsTr("打开文件")
                onClicked: {
                    fileDialog.open()
                }
            }

            Button{
                id: sendBtn
                height: 32
                width: 80
                text: qsTr("发送文件")
                onClicked: {
                    ftTest.cls_subSendFile(fileDialog.file, inputIP.text, inputPort.text);
                }
            }

            Column{
                spacing: 2

                Row{
                    Text {
                        text: qsTr("文件大小: ")
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: txtFileSize
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 14
                        color: "#eeff0000"
                    }
                }
                Row{
                    Text {
                        text: qsTr("总体耗时: ")
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: txtTotalTime
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 14
                        color: "#eeff0000"
                    }
                }
                Row{
                    Text {
                        text: qsTr("平均速度: ")
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: txtSpeed
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 14
                        color: "#eeff0000"
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFile
        nameFilters: ["所有文件 (*.*)"]
        options :FileDialog.ReadOnly
    }

    Connections{
        target: ftTest
        ignoreUnknownSignals: true
        onSSetProgressMax:{
            progressBar.from = 0;
            progressBar.to = nMax;
        }
        onSSetProgressValue:{
            progressBar.value = nValue;
        }
        onSSetIPList:{
            ipListModel.append({"text": strText});
            ipList.currentIndex = 0;
        }
        onSSetProgressSpeed:{
            txtFileSize.text = strFileSize;
            txtTotalTime.text = strTotalTime
            txtSpeed.text = strSpeed;
        }
    }
}
