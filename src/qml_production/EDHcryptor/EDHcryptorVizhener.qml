import QtQuick 2.0
import QtQuick.Controls 1.4

import VizhenerTextKey 1.0

ApplicationWindow {
    id: edhCryptorVizhener
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("EDHcryptor Vizhener")

    VTextKey {
        id: vTextKey
    }

    TextArea {
        id: inputText
        width: edhCryptorVizhener.width / 2
        height: edhCryptorVizhener.height / 10 * 9
        wrapMode: TextEdit.Wrap

        function setTextToCPP()
        {
            vTextKey.text = inputText.text
        }
    }

    TextArea {
        id: outputText
        readOnly: true
        width: edhCryptorVizhener.width / 2
        height: edhCryptorVizhener.height / 10 * 9
        anchors.left: inputText.right
        wrapMode: TextEdit.Wrap

        function getTextFromCPP()
        {
            outputText.text = vTextKey.text
        }
    }

    TextField {
        id: key
        placeholderText: qsTr("Enter key")
        echoMode: TextInput.Password
        width: edhCryptorVizhener.width / 2
        height: edhCryptorVizhener.height / 20
        anchors.top: inputText.bottom

        function setKeyToCPP()
        {
            vTextKey.key = key.text
        }
    }

    TextField {
        id: foundKey
        enabled: false
        placeholderText: qsTr("Found Key")
        readOnly: true
        width: edhCryptorVizhener.width / 2
        height: edhCryptorVizhener.height / 20
        anchors.top: outputText.bottom
        anchors.left: buttonHack.right

        function getKeyFromCPP()
        {
            foundKey.text = vTextKey.key
        }
    }

    Button {
        id: buttonEncrypt
        enabled: key.length != 0 && inputText.length != 0
        width: edhCryptorVizhener.width / 6
        height: edhCryptorVizhener.height / 20
        anchors.top: key.bottom

        text: "Encrypt Text"
        onClicked: {
            inputText.setTextToCPP()
            key.setKeyToCPP()
            vTextKey.encrypt()
            outputText.getTextFromCPP()
            inputText.text = ""
            key.text = ""
        }
    }

    Button {
        id: buttonDecrypt
        enabled: key.length != 0 && inputText.length != 0
        width: edhCryptorVizhener.width / 6
        height: edhCryptorVizhener.height / 20
        anchors.top: key.bottom
        anchors.left: buttonEncrypt.right

        text: "Decrypt Text"
        onClicked: {
            inputText.setTextToCPP()
            key.setKeyToCPP()
            vTextKey.decrypt()
            outputText.getTextFromCPP()
            inputText.text = ""
            key.text = ""
        }
    }

    Button {
        id: buttonHack
        enabled: inputText.length != 0
        width: edhCryptorVizhener.width / 6
        height: edhCryptorVizhener.height / 20
        anchors.top: key.bottom
        anchors.left: buttonDecrypt.right

        text: "Hack Text"
        onClicked: {
            inputText.setTextToCPP()
            vTextKey.hack()
            foundKey.getKeyFromCPP()
            outputText.getTextFromCPP()
        }
    }

    Button {
        id: languageEnglish
        enabled: vTextKey.language != "english"
        width: edhCryptorVizhener.width / 8
        height: edhCryptorVizhener.height / 20
        anchors.top: foundKey.bottom
        anchors.left: buttonHack.right

        text: "eng"
        onClicked: {
            vTextKey.language = "english"
        }
    }

    Button {
        id: languageRussian
        enabled: vTextKey.language != "russian"
        width: edhCryptorVizhener.width / 8
        height: edhCryptorVizhener.height / 20
        anchors.top: foundKey.bottom
        anchors.left: languageEnglish.right

        text: "ru"
        onClicked: {
            vTextKey.language = "russian"
        }
    }

    Button {
        id: buttonClean
        width: edhCryptorVizhener.width / 8
        height: edhCryptorVizhener.height / 20
        anchors.top: foundKey.bottom
        anchors.left: languageRussian.right

        text: "clean"
        onClicked: {
            vTextKey.text = ""
            vTextKey.key = ""
            inputText.text = ""
            outputText.text = ""
            key.text = ""
            foundKey.text = ""
        }
    }

    Loader {
        id: menuLoader
    }

    Button {
        id: buttonMenu
        width: edhCryptorVizhener.width / 8
        height: edhCryptorVizhener.height / 20
        anchors.top: foundKey.bottom
        anchors.left: buttonClean.right

        text: "menu"
        onClicked: {
            menuLoader.source = ""
            menuLoader.source = "EDHcryptorMenu.qml"
            edhCryptorVizhener.close()
        }
    }
}


