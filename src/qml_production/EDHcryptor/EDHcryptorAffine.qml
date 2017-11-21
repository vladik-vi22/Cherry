import QtQuick 2.0
import QtQuick.Controls 1.2

import AffineTextKeys 1.0

ApplicationWindow
{
    id: edhCryptorAffine
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("EDHcryptor Affine")

    ATextKeys
    {
        id: aTextKeys
    }

    TextArea
    {
        id: inputText
        width: edhCryptorAffine.width / 2
        height: edhCryptorAffine.height / 10 * 9
        wrapMode: TextEdit.Wrap

        function setTextToCPP()
        {
            aTextKeys.text = inputText.text
        }
    }

    TextArea
    {
        id: outputText
        readOnly: true
        width: edhCryptorAffine.width / 2
        height: edhCryptorAffine.height / 10 * 9
        anchors.left: inputText.right
        wrapMode: TextEdit.Wrap

        function getTextFromCPP()
        {
            outputText.text = aTextKeys.text
        }
    }

    TextField
    {
        id: key1
        placeholderText: qsTr("Enter first key")
        echoMode: TextInput.Password
        width: edhCryptorAffine.width / 4
        height: edhCryptorAffine.height / 20
        anchors.top: inputText.bottom

        function setKeyToCPP()
        {
            aTextKeys.key1 = key1.text
        }
    }

    TextField
    {
        id: key2
        placeholderText: qsTr("Enter second key")
        echoMode: TextInput.Password
        width: edhCryptorAffine.width / 4
        height: edhCryptorAffine.height / 20
        anchors.top: inputText.bottom
        anchors.left: key1.right

        function setKeyToCPP()
        {
            aTextKeys.key2 = key2.text
        }
    }

    TextField
    {
        id: foundKey1
        enabled: false
        placeholderText: qsTr("Found first key")
        readOnly: true
        width: edhCryptorAffine.width / 4
        height: edhCryptorAffine.height / 20
        anchors.top: outputText.bottom
        anchors.left: buttonHack.right

        function getKeyFromCPP()
        {
            foundKey1.text = aTextKeys.key1
        }
    }

    TextField
    {
        id: foundKey2
        enabled: false
        placeholderText: qsTr("Found second key")
        readOnly: true
        width: edhCryptorAffine.width / 4
        height: edhCryptorAffine.height / 20
        anchors.top: outputText.bottom
        anchors.left: foundKey1.right

        function getKeyFromCPP()
        {
            foundKey2.text = aTextKeys.key2
        }
    }

    Button
    {
        id: buttonEncrypt
        enabled: key1.length != 0 && key2.length != 0 && inputText.length != 0
        width: edhCryptorAffine.width / 6
        height: edhCryptorAffine.height / 20
        anchors.top: key1.bottom

        text: "Encrypt Text"
        onClicked: {
            inputText.setTextToCPP()
            key1.setKeyToCPP()
            key2.setKeyToCPP()
            aTextKeys.encrypt()
            outputText.getTextFromCPP()
            inputText.text = ""
            key1.text = ""
            key2.text = ""
        }
    }

    Button
    {
        id: buttonDecrypt
        enabled: key1.length != 0 && key2.length != 0 && inputText.length != 0
        width: edhCryptorAffine.width / 6
        height: edhCryptorAffine.height / 20
        anchors.top: key1.bottom
        anchors.left: buttonEncrypt.right

        text: "Decrypt Text"
        onClicked: {
            inputText.setTextToCPP()
            key1.setKeyToCPP()
            key2.setKeyToCPP()
            aTextKeys.decrypt()
            outputText.getTextFromCPP()
            inputText.text = ""
            key1.text = ""
            key2.text = ""
        }
    }

    Button
    {
        id: buttonHack
        enabled: inputText.length != 0
        width: edhCryptorAffine.width / 6
        height: edhCryptorAffine.height / 20
        anchors.top: key2.bottom
        anchors.left: buttonDecrypt.right

        text: "Hack Text"
        onClicked: {
            inputText.setTextToCPP()
            aTextKeys.hack()
            foundKey1.getKeyFromCPP()
            foundKey2.getKeyFromCPP()
            outputText.getTextFromCPP()
        }
    }

    Button
    {
        id: languageEnglish
        enabled: aTextKeys.language != "english"
        width: edhCryptorAffine.width / 8
        height: edhCryptorAffine.height / 20
        anchors.top: foundKey1.bottom
        anchors.left: buttonHack.right

        text: "eng"
        onClicked: {
            aTextKeys.language = "english"
        }
    }

    Button
    {
        id: languageRussian
        enabled: aTextKeys.language != "russian"
        width: edhCryptorAffine.width / 8
        height: edhCryptorAffine.height / 20
        anchors.top: foundKey1.bottom
        anchors.left: languageEnglish.right

        text: "ru"
        onClicked: {
            aTextKeys.language = "russian"
        }
    }

    Button
    {
        id: buttonClean
        width: edhCryptorAffine.width / 8
        height: edhCryptorAffine.height / 20
        anchors.top: foundKey2.bottom
        anchors.left: languageRussian.right

        text: "clean"
        onClicked: {
            aTextKeys.text = ""
            aTextKeys.key1 = ""
            aTextKeys.key2 = ""
            inputText.text = ""
            outputText.text = ""
            key1.text = ""
            key2.text = ""
            foundKey1.text = ""
            foundKey2.text = ""
        }
    }

    Loader
    {
        id: menuLoader
    }

    Button
    {
        id: buttonMenu
        width: edhCryptorAffine.width / 8
        height: edhCryptorAffine.height / 20
        anchors.top: foundKey2.bottom
        anchors.left: buttonClean.right

        text: "menu"
        onClicked: {
            menuLoader.source = ""
            menuLoader.source = "EDHcryptorMenu.qml"
            edhCryptorAffine.close()
        }
    }
}



