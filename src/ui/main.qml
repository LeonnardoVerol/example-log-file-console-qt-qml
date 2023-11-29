import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import LogManager

ApplicationWindow {
    id: mainWindow

    minimumWidth: 640
    minimumHeight: 480
    width: 800
    height: 600
    visible: true
    title: qsTr("Example Log to File and to Fake Console")

    property var fakeConsoleWindow
    Component.onCompleted: {
        const debugConsoleComponent  = Qt.createComponent("qrc:/ui/FakeConsoleWindow.qml");

        // If a parent is not provided to createObject(), a reference to the returned object must be
        // held so that it is not destroyed by the garbage collector.
        // And we need it without a parent so it is a top-level window
        if(typeof(mainWindow.fakeConsoleWindow) === "undefined")
            mainWindow.fakeConsoleWindow = debugConsoleComponent.createObject();

        mainWindow.fakeConsoleWindow.show();
    }
    onClosing: (close) => Qt.quit() // This will also close the fake console window if open

    ColumnLayout {
        anchors.centerIn: parent

        /*
         * on C++, you can also use the following:
         *
         * qDebug()
         * qInfo()
         * qWarn()
         * qCritical()
         * qFatal()
         *
        */

        Button {
            text: "Add Debug Log"

            onClicked: console.log("New Debug Log")
        }

        Button {
            text: "Add Info Log"

            onClicked: console.info("New Info Log")
        }

        Button {
            text: "Add Warn Log"

            onClicked: console.warn("New Warn Log")
        }

        Button {
            text: "Add Critical Log"

            onClicked: console.error("New Critical Log")
        }
    }
}
