import QtQuick 2.0
import QtQuick.Controls 1.2

ApplicationWindow
{
    id: menuPRBgenerators
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("Menu PRBgenerators")

    property int numberOfButton: 3

    Loader
    {
        id: prbGeneratorsLoader
    }

    Button
    {
        id: buttonGeneratorsTests
        anchors.top: menuPRBgenerators.top
        width: menuPRBgenerators.width
        height: menuPRBgenerators.height / numberOfButton
        text: "PRB Generators && Tests"

        onClicked:
        {
            prbGeneratorsLoader.source = ""
            prbGeneratorsLoader.source = "PRBGeneratorsNTests.qml"
            menuPRBgenerators.close()
        }
    }

    Button
    {
        id: buttonMenu
        anchors.top: buttonGeneratorsTests.bottom
        width: menuPRBgenerators.width
        height: menuPRBgenerators.height / numberOfButton
        text: "Menu"

        onClicked:
        {
            prbGeneratorsLoader.source = ""
            prbGeneratorsLoader.source = "../main.qml"
            menuPRBgenerators.close()
        }
    }

    Button
    {
        id: buttonExit
        anchors.top: buttonMenu.bottom
        width: menuPRBgenerators.width
        height: menuPRBgenerators.height / numberOfButton
        text: "Exit"

        onClicked:
        {
            menuPRBgenerators.close()
        }
    }
}
