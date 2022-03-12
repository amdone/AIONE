import QtQuick 2.0

Rectangle {
    id: imageViewer
    implicitWidth: 1280
    implicitHeight: 960
    color: 'black'
    property int imageWidth: 0
    property int imageHeight: 0
    property string imagePath: ""
    property double initScale: 1.0
    Rectangle {
        id: imageDisplay
        width: 1280
        height: 960

        Image {
            id: img
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: {
                if(imagePath === ""){
                    ""
                }else{
                    "file:///" + imagePath
                }
            }

            onVisibleChanged: {
                console.log(imageDisplay.scale)
                imageDisplay.scale = 1
            }
        }
        MouseArea {
            anchors.fill: parent
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



    }
    Connections {
        target: imageContainer
        onResetViewer: {
            imageDisplay.scale = 1
        }
    }

}
