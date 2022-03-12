import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4
import QtQml 2.12
import QtQuick.Dialogs 1.2

Rectangle {
    id: imageContainer
    //objectName: "rightButtonMenu"
    //signal popImage(Number index);
    property var index: -1
    property bool choosen: false
    property int realWidth: 0
    property int realHeight: 0
    signal sendInfo(string info)
    width: 200
    height: 200

    Rectangle {
        id: image
        color: 'gray'
        anchors.fill: parent
        anchors.margins: 10
        border.width: 3
        MouseArea {
            id: mouseRegion
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            hoverEnabled: true

            onClicked: {
                if (mouse.button === Qt.RightButton) {
                    option_menu.popup()
                }else if(mouse.button === Qt.LeftButton){
                    imageViewDialog.open()
                }
            }
            onEntered: {
                let info = "Index: " + imageContainer.index + " Choosen: " + imageContainer.index
                imageContainer.sendInfo(info)
            }
            onExited: {
                let info = ""
                imageContainer.sendInfo(info)
            }
        }

        Menu {
            id: option_menu
            MenuItem {
                text: qsTr("Pop")
                onTriggered: {
                    choosen = false
                    image.opacity = 0.15
                }
            }

            MenuItem {
                text: qsTr("Set to cover")
                onTriggered: {

                }
            }

            MenuItem {
                text: qsTr("Rechoose")
                onTriggered: {
                    choosen = true
                    image.opacity = 1
                }
            }

            MenuItem {
                text: qsTr("View")
                onTriggered: {
                    imageViewDialog.open()
                }
            }

            MenuItem {
                text: qsTr("Information")
                onTriggered: {
                    imageInfoDialog.open()
                }
            }

            MenuSeparator {}

            Menu {
                title: qsTr("More Stuff")

                MenuItem {
                    text: "Noting"
                }
            }
        }

        Dialog {
            id: imageViewDialog
            title: qsTr("View")
            modality: Qt.NonModal
            contentItem: Rectangle {
                color: "lightskyblue"
                implicitWidth: 400
                implicitHeight: 100
                Text {
                    text: imageContainer.index + ' ' + imageContainer.choosen
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

        Dialog {
            id: imageInfoDialog
            title: qsTr("Information")
            modality: Qt.NonModal
            contentItem: Rectangle {
                color: "lightskyblue"
                implicitWidth: 400
                implicitHeight: 100
                Text {
                    text: imageContainer.index
                    color: "navy"
                    anchors.centerIn: parent
                }
            }
        }

    }
}
