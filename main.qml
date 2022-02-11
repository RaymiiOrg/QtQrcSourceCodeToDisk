import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2 as QDiag

import org.raymii.SaveToDisk 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    readonly property string exampleFile: ":/files/example.png"
    readonly property string sourceArchive: ":/source.zip"

    ScrollView {
        anchors.fill: parent
        anchors.margins: 20

        ColumnLayout {
            spacing: 5

            Text {
                text: "Example Image"
            }

            Image {
                id: exampleImg
                source: "qrc" + exampleFile
                Layout.preferredWidth: 400
                Layout.preferredHeight: 300
            }

            Button {
                text: "Save image to disk"
                onClicked: {
                    if (SaveToDisk.save(exampleFile)) {
                        placeholderDialog.success = true
                    }
                    placeholderDialog.open()
                }
            }

            Button {
                text: "Save source code archive to disk"
                onClicked: {
                    if (SaveToDisk.save(sourceArchive)) {
                        placeholderDialog.success = true
                    }
                    placeholderDialog.open()
                }
            }

            Text {
                text: "C++ / Qt example by Raymii.org to \nsave embedded qrc:/ resource to disk"
            }

            Text {
                text: "and create source code archive to \nship source with app, which can be extracted."
            }
        }
    }

    QDiag.MessageDialog {
        id: placeholderDialog
        property bool success: false
        property string folder: SaveToDisk.getDocumentsFolder()
        title: "File saved"
        text: success ? "File is saved to: " + folder : "Failed to save file to " + folder
    }
}
