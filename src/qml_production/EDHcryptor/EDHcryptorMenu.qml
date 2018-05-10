import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: menuEDHcryptor
    visible: true
    width: parent.width
    height: parent.height
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
            edhCryptorLoader.source = "EDHcryptorVizhener.qml"
            menuEDHcryptor.close()
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
            edhCryptorLoader.source = "EDHcryptorAffine.qml"
            menuEDHcryptor.close()
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
            edhCryptorLoader.source = "../main.qml"
            menuEDHcryptor.close()
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
