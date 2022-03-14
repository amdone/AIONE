import QtQuick 2.0
import QtQuick.Dialogs 1.3

//图片预览对话框
Dialog {
    id: imageViewDialog
    title: qsTr("View")
    modality: Qt.NonModal
    property int imageWidth: 0
    property int imageHeight: 0
    property string imagePath: ""
    property real scale_factor: scaleFactor(imageWidth, imageHeight)
    //property double initScale: 1.0
    contentItem: Rectangle {
        id: imageViewer
        implicitWidth: imageWidth * scale_factor
        implicitHeight: imageHeight * scale_factor
        color: 'black'
        MouseArea {
            anchors.fill: parent
            drag.target: imageDisplay
            onWheel: {
                if (wheel.modifiers & Qt.ControlModifier) {
                    imageDisplay.rotation += wheel.angleDelta.y / 120 * 5
                    if (Math.abs(imageDisplay.rotation) < 4)
                        imageDisplay.rotation = 0
                } else {
                    imageDisplay.rotation += wheel.angleDelta.x / 120
                    if (Math.abs(imageDisplay.rotation) < 0.6)
                        imageDisplay.rotation = 0
                    var scaleBefore = imageDisplay.scale
                    imageDisplay.scale += imageDisplay.scale * wheel.angleDelta.y / 120 / 10
                }
            }
        }
        Rectangle {
            id: imageDisplay
            width: imageWidth * scale_factor
            height: imageHeight * scale_factor

            Image {
                id: img
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                cache: true
                source: {
                    if (imageViewDialog.imagePath === "") {
                        ""
                    } else {
                        "file:///" + imageViewDialog.imagePath
                    }
                }
            }
        }
    }
    onVisibilityChanged: {
        if (visible === false) {
            imageViewDialog.destroy()
        }
    }

    function scaleFactor(width, height) {
        if (width >= 1600 && height <= 860)
            return 1600.0 / width
        if (width <= 1600 && height >= 860)
            return 860.0 / height
        if (width >= 1600 && height >= 860) {
            scale = 1600.0 / width
            if (height * scale <= 860)
                return scale
            else {
                return 860.0 / height
            }
        }
        return 1.0
    }
}
