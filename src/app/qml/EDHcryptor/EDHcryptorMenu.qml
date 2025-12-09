import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    id: menuEDHcryptor
    visible: true
    width: Screen.width / 3
    height: Screen.height / 2
    title: qsTr("Menu EDHcryptor")

    property int numberOfButtons: 4

    Loader {
        id: edhCryptorLoader
    }

    Button {
        id: buttonVizhener
        anchors.top: menuEDHcryptor.top
        width: menuEDHcryptor.width
        height: menuEDHcryptor.height / numberOfButtons
        text: "Vizhener Cipher"

        onClicked: {
            edhCryptorLoader.source = ""
            edhCryptorLoader.source = "qrc:/qt/qml/Cherry/qml/EDHcryptor/EDHcryptorVizhener.qml"
            menuEDHcryptor.hide()
        }
    }

    Button {
        id: buttonAffine
        anchors.top: buttonVizhener.bottom
        width: menuEDHcryptor.width
        height: menuEDHcryptor.height / numberOfButtons
        text: "Affine Cipher"

        onClicked: {
            edhCryptorLoader.source = ""
            edhCryptorLoader.source = "qrc:/qt/qml/Cherry/qml/EDHcryptor/EDHcryptorAffine.qml"
            menuEDHcryptor.hide()
        }
    }

    Button {
        id: buttonMenu
        anchors.top: buttonAffine.bottom
        width: menuEDHcryptor.width
        height: menuEDHcryptor.height / numberOfButtons
        text: "Menu"

        onClicked: {
            edhCryptorLoader.source = ""
            edhCryptorLoader.source = "qrc:/qt/qml/Cherry/qml/main.qml"
            menuEDHcryptor.hide()
        }
    }

    Button {
        id: buttonExit
        anchors.top: buttonMenu.bottom
        width: menuEDHcryptor.width
        height: menuEDHcryptor.height / numberOfButtons
        text: "Exit"

        onClicked: {
            menuEDHcryptor.close()
        }
    }
}
