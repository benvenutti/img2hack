import QtCore
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs

import example 1.0

ApplicationWindow {
    id: root
    visible: true

    width: 800
    height: 1000

    header: ToolBar {
        Button {
            text: qsTr("Load Image...")
            onClicked: fileDialog.open()
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 5

        Button {
            enabled: originalImage.status == Image.Ready
            text: qsTr("Clear image")
            onClicked: {
                originalImage.source = ""
                thresholdSlider.reset();
            }
        }

        Slider {
            id: thresholdSlider
            from: 0.0
            value: 50.0
            to: 100.0
            enabled: originalImage.status == Image.Ready
            width: 300

            function reset() {
                value = 50.0
            }
        }

        Image {
            id: originalImage
            width: 300
            height: 300
            fillMode: Image.Stretch
        }

        BinaryImage {
            width: 300
            height: 300
            imageUrl: originalImage.source
            threshold: thresholdSlider.value
        }
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted: originalImage.source = selectedFile
    }
}
