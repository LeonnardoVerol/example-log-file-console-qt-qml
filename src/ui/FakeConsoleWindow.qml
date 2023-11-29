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

    ScrollView {
        id: myScrollView
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.bottomMargin: 32

        clip: true
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        ListView {
            id: myListView
            anchors.fill: parent
            anchors.leftMargin: 24
            anchors.rightMargin: 24
            spacing: 6

            Connections {
                target: LogManager

                function onAddLineAll(line)
                {
                    myListModel.append({text: line});

                    // Auto-scroll To Bottom if ScrollBar at the End
                    if (myScrollView.contentHeight - myListView.contentY <= 1000)
                        myListView.positionViewAtEnd();
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
                        Layout.maximumWidth: parent.width

                        text: model.text
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
    }
}
