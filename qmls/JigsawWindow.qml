import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4
import QtQml 2.12
import QtQuick.Dialogs 1.2

Rectangle {
    id: jigsawWindow
    objectName: "jigsawWindow"
    property var imagesList: []
    property string skinTheme: "white"
    property string fontColor: "black"
    property string bgColor: "white"
    property string subColor: "white"
    signal imageComponentsIsOk
    signal requestImagePath(int index)
    signal popImageSignal(int index)
    signal pushImageSignal(int index)
    anchors.fill: parent
    color: bgColor
    Row {
        anchors.fill: parent
        spacing: 0

        Column {
            width: parent.width * 0.8
            height: parent.height
            spacing: 0
            //左边预览区
            ScrollView {
                id: galleryView
                width: parent.width
                height: parent.height - 20
                leftPadding: 35
                topPadding: 35
                //contentWidth: gallery.width    // The important part
                //contentHeight: gallery.height
                Grid {
                    id: gallery
                    clip: true
                    columns: 5
                    Component.onCompleted: {

                    }
                }
                onWidthChanged: {
                    let cot = parseInt(galleryView.width / 210)
                    gallery.columns = cot === 0 ? 1 : cot
                    delete cot
                }
            }

            //底部信息区
            Column {
                height: 20
                width: parent.width
                Rectangle {
                    implicitHeight: 1
                    implicitWidth: parent.width
                    color: 'black'
                }
                Rectangle {
                    implicitHeight: 20
                    implicitWidth: parent.width
                    color: bgColor
                    Text {
                        id: textImageInfo
                        text: qsTr("")
                        function changText(info) {
                            text = info
                        }
                    }
                }
            }
        }

        //右边功能区
        Rectangle {
            id: rightArea
            property int borderWidth: 2
            width: parent.width * 0.2 + borderWidth * 2
            height: parent.height + borderWidth * 2
            y: parent.y - borderWidth
            border.width: borderWidth
            color: bgColor

            //换肤按钮
            Button {
                id: btnChangeSkin
                anchors.right: switch_language_row_2.left
                anchors.verticalCenter: switch_language_row_2.verticalCenter
                anchors.rightMargin: 25
                background: Image {
                    id: skinSvg
                    source: "qrc:/icons/skin.svg"
                }
                onClicked: {
                    var qmlComponent = Qt.createComponent("SkinDialog.qml")
                    var skinDialog = qmlComponent.createObject(jigsawWindow)
                    skinDialog.changeTheme.connect(onChangeTheme)
                    skinDialog.changeTheme.connect(jigsawWindow.onChangeTheme)
                    skinDialog.open()
                }
            }

            //语言切换
            Row {
                id: switch_language_row_2
                anchors.right: parent.right
                Label {
                    text: qsTr("Language")
                    anchors.verticalCenter: switch_language_row_2.verticalCenter
                }
                ComboBox {
                    id: switch_language_combox_2
                    model: ['English', '简体中文']
                    currentIndex: qmlLanguage.getLocalLanguage()
                    onActivated: {
                        qmlLanguage.setLanguage(index)
                        currentIndex = index
                    }
                    //ScrollBar.vertical: ScrollBar {}
                }
            }

            //重新选择文件夹按钮
            Rectangle {
                id: btnChooseFloder
                width: parent.width * 0.8
                height: parent.height * 0.05
                anchors.top: switch_language_row_2.bottom
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                border.width: 2
                border.color: fontColor
                radius: 20
                color: subColor
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
                    text: qsTr("Rechoose Floder")
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 12
                    font.weight: Font.Bold
                    //font.pixelSize: 16
                    color: fontColor
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

            //参数调整区
            Rectangle {
                id: parameterAdjust
                color: bgColor
                objectName: "parameterAdjust"
                implicitWidth: parent.width * 0.8
                anchors.top: btnChooseFloder.bottom
                anchors.bottom: btnGenerate.top
                anchors.topMargin: 25
                anchors.bottomMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter
                Column {
                    anchors.fill: parent
                    spacing: 50

                    //样式选择控件
                    Row {
                        width: parent.width
                        spacing: 15
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Style:")
                            font.pixelSize: 20
                            color: fontColor
                        }
                        Text {
                            id: textStyleChoosed
                            property int styleIndex: 0
                            anchors.verticalCenter: parent.verticalCenter
                            color: fontColor
                            text: {
                                if (styleIndex === 0) {
                                    qsTr("Classic")
                                } else if (styleIndex === 1) {
                                    qsTr("Cover")
                                }
                            }

                            font.pixelSize: 20
                        }
                        Button {
                            id: btnChange
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("change")

                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 30
                                opacity: enabled ? 1 : 0.3
                                color: btnChange.down ? "#d0d0d0" : "#ffffff"
                                radius: 15
                                border.width: 1
                            }
                            onClicked: {
                                dialogStyleChange.open()
                            }
                        }
                    }
                    //宽度
                    Row {
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {
                            width: 100
                            anchors.verticalCenter: parent.verticalCenter
                            color: fontColor
                            text: qsTr("Width:")
                            font.pixelSize: 20
                        }
                        TextField {
                            width: 80
                            color: fontColor
                            validator: IntValidator {
                                bottom: 1
                                top: 50000
                            }
                            text: "1920"
                            MouseArea {
                                anchors.fill: parent
                                scrollGestureEnabled: false
                                onClicked: {
                                    parent.focus = true
                                }

                                onWheel: {
                                    let parent_text = Number(parent.text)
                                    parent_text += wheel.angleDelta.y / 120 * 10
                                    if (parent_text < 0) {
                                        parent_text = 0
                                    }
                                    parent.text = parent_text.toString()
                                }
                            }
                        }
                    }
                    //高度
                    Row {
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {
                            width: 100
                            color: fontColor
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Height:")
                            font.pixelSize: 20
                        }
                        TextField {
                            width: 80
                            color: fontColor
                            validator: IntValidator {
                                bottom: 1
                                top: 50000
                            }
                            text: "1080"

                            MouseArea {
                                anchors.fill: parent
                                scrollGestureEnabled: false
                                onClicked: {
                                    parent.focus = true
                                }

                                onWheel: {
                                    let parent_text = Number(parent.text)
                                    parent_text += wheel.angleDelta.y / 120 * 10
                                    if (parent_text < 0) {
                                        parent_text = 0
                                    }
                                    parent.text = parent_text.toString()
                                }
                            }
                        }
                    }
                    //数量
                    Row {
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {
                            width: 100
                            color: fontColor
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Numbers:")
                            font.pixelSize: 20
                        }
                        TextField {
                            width: 80
                            color: fontColor
                            validator: IntValidator {
                                bottom: 1
                                top: 50
                            }
                            text: "12"

                            MouseArea {
                                anchors.fill: parent
                                scrollGestureEnabled: false
                                onClicked: {
                                    parent.focus = true
                                }

                                onWheel: {
                                    let parent_text = Number(parent.text)
                                    parent_text += wheel.angleDelta.y / 120
                                    if (parent_text < 0) {
                                        parent_text = 0
                                    } else if (parent_text > 50) {
                                        parent_text = 50
                                    }
                                    parent.text = parent_text.toString()
                                }
                            }
                        }
                    }
                }
            }

            //生成按钮
            Rectangle {
                id: btnGenerate
                objectName: "btnGenerate"
                width: parent.width * 0.8
                height: parent.height * 0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter
                border.width: 2
                border.color: fontColor
                radius: 20
                color: subColor
                //                Image {
                //                    id: iconChooseFloder
                //                    height: parent.height * 0.8
                //                    width: parent.height * 0.8
                //                    anchors.left: parent.left
                //                    anchors.verticalCenter: parent.verticalCenter
                //                    anchors.margins: 20
                //                    anchors.leftMargin: 20
                //                    source: "icons/folderOpen_black.svg"
                //                }
                Text {
                    id: textGenerate
                    text: qsTr("Generate")
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 12
                    font.weight: Font.Bold
                    //font.pixelSize: 16
                    color: fontColor
                    anchors.centerIn: parent
                }
                MouseArea {
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    onClicked: {

                        //console.log("生成")
                    }
                    onEntered: {
                        textGenerate.opacity = 0.8
                        btnGenerate.opacity = 0.8
                        //iconChooseFloder.opacity = 0.8
                    }
                    onExited: {
                        textGenerate.opacity = 1
                        btnGenerate.opacity = 1
                        //iconChooseFloder.opacity = 1
                    }
                    //按下
                    onPressed: {
                        textGenerate.color = "#2F4F4F"
                        btnGenerate.opacity = 1
                    }

                    //释放
                    onReleased: {
                        textGenerate.color = "black"
                    }
                }
            }

            //样式选择对话框
            Dialog {
                id: dialogStyleChange
                title: qsTr("Choose your style")

                visible: false
                standardButtons: StandardButton.Ok | StandardButton.Cancel
                contentItem: Rectangle {
                    implicitWidth: 500
                    implicitHeight: 200
                    color: bgColor
                    Text {
                        anchors.bottom: radioButtonRow.top
                        anchors.bottomMargin: 25
                        text: qsTr("Choose your style:")
                        font.pixelSize: 25
                        font.bold: true
                        color: fontColor
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    ButtonGroup {
                        id: buttonGroupForStyleChoose
                        buttons: radioButtonRow.children
                        onClicked: {
                            for (var i in buttonGroupForStyleChoose.buttons) {
                                if (buttons[i].checked) {
                                    textStyleChoosed.styleIndex = i
                                    break
                                }
                            }
                        }
                    }
                    Row {
                        id: radioButtonRow
                        property string styleType: 'classic'
                        anchors.centerIn: parent
                        spacing: 50
                        RadioButton {
                            text: qsTr("Classic")
                            checked: true
                        }
                        RadioButton {
                            text: qsTr("Cover")
                        }
                        RadioButton {
                            text: qsTr("Other")
                            checkable: false
                            opacity: 0.5
                        }
                    }
                    Row {
                        anchors.top: radioButtonRow.bottom
                        topPadding: 25
                        anchors.horizontalCenter: parent.horizontalCenter
                        Button {
                            id: btnOk
                            text: qsTr("OK")
                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 30
                                opacity: enabled ? 1 : 0.3
                                color: btnOk.down ? "#d0d0d0" : "#e0e0e0"
                                radius: 15
                            }
                            onClicked: {
                                dialogStyleChange.close()
                            }
                        }
                    }
                }
            }

            //打开文件夹信号绑定
            Connections {
                target: Jigsaw
                ignoreUnknownSignals: true
                function onImagesNumsCall(nums) {
                    var component = Qt.createComponent("LittleImage.qml")
                    for (var i = 0; i < nums; i++) {
                        var object = component.createObject(gallery, {
                                                                "index": i,
                                                                "choosen": true
                                                            })
                        object.sendInfo.connect(textImageInfo.changText)
                        imagesList.push(object)
                        jigsawWindow.requestImagePath(i)
                    }
                    //imageComponentsIsOk()
                }
            }

            Connections {
                target: Jigsaw
                ignoreUnknownSignals: true
                function onImageHasRemoved(index) {
                    //console.log('image ' + index + 'has removed')
                    imagesList[index].destroy()
                    imagesList.splice(index)
                }
            }

            Connections {
                target: Jigsaw
                ignoreUnknownSignals: true
                function onReturnImagePath(index, path) {
                    imagesList[index].imagePath = path
                }
            }
        }
    }

    function onChangeTheme(themeColor) {
        switch (themeColor) {
        case "white":
            bgColor = themeColor
            fontColor = "black"
            subColor = "white"
            skinSvg.source = "qrc:/icons/skin.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_black.svg"
            break
        case "black":
            bgColor = themeColor
            fontColor = "white"
            subColor = "#454545"
            skinSvg.source = "qrc:/icons/skin_white.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_white.svg"
            break
        case "red":
            bgColor = "#712626"
            subColor = "#562929"
            fontColor = "white"
            skinSvg.source = "qrc:/icons/skin_white.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_white.svg"
            break
        case "blue":
            bgColor = "#006F87"
            subColor = "#004E60"
            fontColor = "white"
            skinSvg.source = "qrc:/icons/skin_white.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_white.svg"
            break
        case "gray":
            bgColor = "#666666"
            subColor = "#454545"
            fontColor = "white"
            skinSvg.source = "qrc:/icons/skin_white.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_white.svg"
            break
        case "green":
            bgColor = "#2D8F31"
            subColor = "#0D5B00"
            fontColor = "white"
            skinSvg.source = "qrc:/icons/skin_white.svg"
            iconChooseFloder.source = "qrc:/icons/folderOpen_white.svg"
            break
        default:
            break
        }
    }
}
