import QtQuick 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.12 as Controls
import QtQuick.Controls.Styles 1.4

//样式选择对话框
Dialog {
    id: skinDialog
    title: qsTr("Choose your skin")
    //standardButtons: StandardButton.Ok | StandardButton.Cancel
    contentItem: Rectangle {
        id: skinDisplay
        implicitWidth: 1200
        implicitHeight: 800
        Text {
            anchors.top: skinDisplay.top
            anchors.topMargin: 25
            text: qsTr("Choose your skin:")
            font.pixelSize: 25
            font.bold: true
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Grid {
            id: skinGrid
            anchors.top: skinDisplay.top
            anchors.topMargin: 50
            anchors.horizontalCenter:skinDisplay.horizontalCenter
            columns: 3
            spacing: 50
            Rectangle {
                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: white
                    source: "qrc:/images/skin_white.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            Rectangle {
                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: black
                    source: "qrc:/images/skin_black.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            Rectangle {
                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: gray
                    source: "qrc:/images/skin_gray.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            Rectangle {
                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: green
                    source: "qrc:/images/skin_green.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            Rectangle {

                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: red
                    source: "qrc:/images/skin_red.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            Rectangle {

                implicitHeight: 300
                implicitWidth: 300
                Image {
                    id: blue
                    source: "qrc:/images/skin_blue.jpg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    onVisibleChanged: {
        if (visible === false) {
            skinDialog.destroy()
        }
    }
}
