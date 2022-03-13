import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4
import QtQml 2.12
import QtQuick.Dialogs 1.2

Window {
    id: mainWindow
    property var mainWindowWidth: Screen.width * 0.835
    property var mainWindowHeight: Screen.height * 0.8
    visible: true
    width: mainWindowWidth
    height: mainWindowHeight
    title: "AIONE"

    //主界面的大矩形
    Rectangle {
        id: mainPage
        anchors.fill: parent

        Button {
            id: btnChangeSkin
            anchors.right: switch_language_row.left
            anchors.verticalCenter: switch_language_row.verticalCenter
            anchors.rightMargin: 25
            background: Image {
                id: skinSvg
                source: "qrc:/icons/skin.svg"
            }
            onClicked: {
                var qmlComponent = Qt.createComponent("SkinDialog.qml")
                var skinDialog = qmlComponent.createObject(mainPage)
                skinDialog.open()
            }
        }

        //切换语言控件
        Row {
            id: switch_language_row
            anchors.right: parent.right
            Label {
                text: qsTr("Language")
                anchors.verticalCenter: switch_language_row.verticalCenter
            }
            ComboBox {
                id: switch_language_combox
                model: ['English', '简体中文']
                currentIndex: qmlLanguage.getLocalLanguage()
                onActivated: {
                    qmlLanguage.setLanguage(index)
                    currentIndex = index
                }
                //ScrollBar.vertical: ScrollBar {}
            }
        }

        //打开文件夹按钮
        Rectangle {
            id: btnChooseFloder
            width: parent.width * 0.4
            height: parent.height * 0.1
            anchors.centerIn: parent
            border.width: 2
            border.color: "black"
            radius: 20
            opacity: 0.7
            Image {
                id: iconChooseFloder
                height: parent.height * 0.8
                width: parent.height * 0.8
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 20
                anchors.leftMargin: 20
                source: "qrc:/icons/folderOpen_black.svg"
            }
            Text {
                id: textChooseFloder
                text: qsTr("Choose Floder")
                font.pointSize: (mainWindow.width * 0.02) ? (mainWindow.width * 0.02) : 15
                font.weight: Font.Bold
                color: "black"
                anchors.left: iconChooseFloder.right
                leftPadding: parent.width * 0.15
                anchors.verticalCenter: parent.verticalCenter
            }
            MouseArea {
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                anchors.fill: parent
                onClicked: {
                    floderDialog.open()

                }
                onEntered: {
                    textChooseFloder.opacity = 0.8
                    btnChooseFloder.opacity = 0.8
                    iconChooseFloder.opacity = 0.8
                }
                onExited: {
                    textChooseFloder.opacity = 1
                    btnChooseFloder.opacity = 1
                    iconChooseFloder.opacity = 1
                }
                //按下
                onPressed: {
                    textChooseFloder.color = "#2F4F4F"
                    textChooseFloder.opacity = 1
                }

                //释放
                onReleased: {
                    textChooseFloder.color = "black"
                }
            }
        }

        //选择文件对话框
        FileDialog {
            id: floderDialog
            objectName: "floderDialog"
            title: qsTr("Please choose a Floder")
            selectFolder: true
            signal openForlder(string filepath);
            onAccepted: {
                console.log(fileUrl)
                mainPage.visible = false
                jigsawWindow.visible = true
                if(jigsawWindow.imagesList === undefined){
                    openForlder(fileUrl)
                }else{
                    for (var i = 0; i < jigsawWindow.imagesList.length; i++) {
                        if (jigsawWindow.imagesList[i].choosen === false) {
                            jigsawWindow.popImageSignal(i)
                        } else {
                            jigsawWindow.pushImageSignal(i)
                        }
                        jigsawWindow.imagesList[i].destroy()
                    }
                    jigsawWindow.imagesList.length = 0
                    openForlder(fileUrl)
                }



            }
        }
    }


    //拼图界面
    JigsawWindow {
        id: jigsawWindow
        visible: false
    }


}


