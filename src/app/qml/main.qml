import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow
{
    id: menu
    visible: true
    width: Screen.width / 3
    height: Screen.height / 2
    title: qsTr("Menu")

    property int numberOfButtons: 4

    Loader
    {
        id: menuLoader
    }

    Button
    {
        id: bigIntCalculator
        anchors.top: menu.top
        width: menu.width
        height: menu.height / numberOfButtons
        text: "BigIntegerCalculator"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "qrc:/qt/qml/Cherry/qml/BigIntLibrary/BigIntCalculator.qml"
            menu.hide()
        }
    }

    Button
    {
        id: prbGeneratorsMenu
        anchors.top: bigIntCalculator.bottom
        width: menu.width
        height: menu.height / numberOfButtons
        text: "PRBgenerators"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "qrc:/qt/qml/Cherry/qml/PRBgenerators/PRBgeneratorsNtests.qml"
            menu.hide()
        }
    }

    Button
    {
        id: edhCryptorMenu
        anchors.top: prbGeneratorsMenu.bottom
        width: menu.width
        height: menu.height / numberOfButtons
        text: "EDHcryptor"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "qrc:/qt/qml/Cherry/qml/EDHcryptor/EDHcryptorMenu.qml"
            menu.hide()
        }
    }

    Button
    {
        id: buttonExit
        anchors.top: edhCryptorMenu.bottom
        width: menu.width
        height: menu.height / numberOfButtons
        text: "Exit"

        onClicked:
        {
            menu.close()
        }
    }

}
