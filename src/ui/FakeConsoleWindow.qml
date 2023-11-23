import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import LogManager

ApplicationWindow {
    id: fakeConsoleWindow

    title: qsTr("%1 - Fake Console Window").arg(Qt.application.name)
    minimumWidth: 640
    minimumHeight: 480
    width: 800
    height: 600

    ListView {
        anchors.fill: parent

        Connections {
            target: LogManager

            function onAddLineAll(line)
            {
                myListModel.append({text: line})
            }
        }

        model: ListModel {
            id: myListModel
        }

        delegate: ItemDelegate {
            width: (parent != null) ? parent.width : undefined
            implicitHeight: textList.implicitHeight

            ColumnLayout {
                id: textList
                anchors.fill: parent
                spacing: 0

                Text {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    text: model.text
                }
            }
        }
    }
}
