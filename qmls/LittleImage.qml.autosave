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
    property int imageWidth: 0
    property int imageHeight: 0
    property int imageFileSize: 0
    property string imagePath: ""
    signal sendInfo(string info)
    signal resetViewer
    signal setCover(int index)
    width: 200
    height: 200

    //单个小图片
    Rectangle {
        id: image
        anchors.fill: parent
        anchors.margins: 10
        Image {
            id: little_image
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            cache: false
            asynchronous: true
            source: {
                if (imagePath === "") {
                    ""
                } else {
                    "file:///" + imagePath
                }
            }
            sourceSize: Qt.size(200, 200)
        }

        MouseArea {
            id: mouseRegion
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            hoverEnabled: true

            onClicked: {
                if (mouse.button === Qt.RightButton) {
                    option_menu.popup()
                } else if (mouse.button === Qt.LeftButton) {
                    var qmlComponent = Qt.createComponent("Viewer.qml")
                    var viewerDialog = qmlComponent.createObject(image, {
                                                                     "imagePath": imagePath,
                                                                     "imageWidth": imageWidth,
                                                                     "imageHeight": imageHeight
                                                                 })
                    viewerDialog.open()
                }
            }
            onEntered: {
                let info = "Index: " + imageContainer.index + "  Choosen: "
                    + imageContainer.choosen + "  WxH: " + imageWidth + "x" + imageHeight
                    + "  FileSize: " + imageFileSize + "  FilePath: " + imagePath
                imageContainer.sendInfo(info)
            }
            onExited: {
                let info = ""
                imageContainer.sendInfo(info)
            }
        }

        //鼠标右键菜单
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
                    setCover(index)
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
                    var qmlComponent = Qt.createComponent("Viewer.qml")
                    var viewerDialog = qmlComponent.createObject(image, {
                                                                     "imagePath": imagePath
                                                                 })
                    viewerDialog.open()
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

        //图片信息对话框
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
