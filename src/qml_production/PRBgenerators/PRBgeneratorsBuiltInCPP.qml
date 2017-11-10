import QtQuick 2.0
import QtQuick.Controls 1.2

import BuiltInCPPNumber 1.0

ApplicationWindow {
    id: prdGeneratorsBuiltInCPP
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("PRBgenerator Built-in CPP")

    BICPPNumber {
        id: bicppNumber
    }

    TextArea {
        id: generatedNumber
        width: prdGeneratorsBuiltInCPP.width / 2
        height: prdGeneratorsBuiltInCPP.height
        wrapMode: TextEdit.Wrap

        function getNumberFromCPP()
        {
            for(var i = 0; i < 2222; i++)
                generatedNumber.text += bicppNumber.number_str[i]
        }
    }

    Button {
        id: buttonGenerate
        width: prdGeneratorsBuiltInCPP.width / 2
        height: prdGeneratorsBuiltInCPP.height / 10
        anchors.left: generatedNumber.right

        text: "Generate"
        onClicked: {
            bicppNumber.generate()
            generatedNumber.getNumberFromCPP()
        }
    }

    Loader {
        id: menuLoader
    }

    Button {
        id: buttonMenu
        width: prdGeneratorsBuiltInCPP.width / 2
        height: prdGeneratorsBuiltInCPP.height / 10
        anchors.top: buttonGenerate.bottom
        anchors.left: generatedNumber.right

        text: "menu"
        onClicked: {
            menuLoader.source = ""
            menuLoader.source = "PRBgeneratorsMenu.qml"
            prdGeneratorsBuiltInCPP.close()
        }
    }

}
