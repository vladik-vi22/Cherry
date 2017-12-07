import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow
{
    id: menu
    visible: true
    width: Screen.width / 3
    height: Screen.height / 2
    title: qsTr("Menu")

    property int numberOfButton: 4

    Loader
    {
        id: menuLoader
    }

    Button
    {
        id: bigIntCalculator
        anchors.top: menu.top
        width: menu.width
        height: menu.height / numberOfButton
        text: "BigIntegerCalculator"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "BigIntLibrary/BigIntCalculator.qml"
            menu.close()
        }
    }

    Button
    {
        id: prbGeneratorsMenu
        anchors.top: bigIntCalculator.bottom
        width: menu.width
        height: menu.height / numberOfButton
        text: "PRBgenerators"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "PRBgenerators/PRBgeneratorsNtests.qml"
            menu.close()
        }
    }

    Button
    {
        id: edhCryptorMenu
        anchors.top: prbGeneratorsMenu.bottom
        width: menu.width
        height: menu.height / numberOfButton
        text: "EDHcryptor"

        onClicked:
        {
            menuLoader.source = ""
            menuLoader.source = "EDHcryptor/EDHcryptorMenu.qml"
            menu.close()
        }
    }

    Button
    {
        id: buttonExit
        anchors.top: edhCryptorMenu.bottom
        width: menu.width
        height: menu.height / numberOfButton
        text: "Exit"

        onClicked:
        {
            menu.close()
        }
    }

}
