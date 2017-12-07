import QtQuick 2.3
import QtQuick.Controls 1.2

import BigIntLibrary 2.0

ApplicationWindow
{
    id: bigIntCalculator
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("Calculator")

    BigIntNumbersBases
    {
        id: bigIntNumbersBases
    }

    Text
    {
        id: textInputBase
        text: "input base:"
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: bigIntCalculator.top
        anchors.left: bigIntCalculator.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Button
    {
        id: baseInputBinary
        enabled: bigIntNumbersBases.baseInput != 2
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textInputBase.top
        anchors.left: textInputBase.right

        text: "bin"
        onClicked:
        {
            bigIntNumbersBases.baseInput = 2
        }
    }

    Button
    {
        id: baseInputDecimal
        enabled: bigIntNumbersBases.baseInput != 10
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textInputBase.top
        anchors.left: baseInputBinary.right

        text: "dec"
        onClicked:
        {
            bigIntNumbersBases.baseInput = 10
        }
    }

    Button
    {
        id: baseInputHexadecimal
        enabled: bigIntNumbersBases.baseInput != 16
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textInputBase.top
        anchors.left: baseInputDecimal.right

        text: "hex"
        onClicked:
        {
            bigIntNumbersBases.baseInput = 16
        }
    }

    TextArea
    {
        id: bigNumber1
        width: bigIntCalculator.width / 5 * 4
        height: bigIntCalculator.height / 10 * 3
        anchors.top: textInputBase.bottom
        anchors.left: bigIntCalculator.left
        wrapMode: TextEdit.Wrap

        onTextChanged:
        {
            if(text.length > 1 && text.charAt(0) === '0')
            {
                remove(0, 1)
                cursorPosition = 1
            }
        }

        function setBigNumber1ToCPP()
        {
            bigIntNumbersBases.bigNumber1 = bigNumber1.text
        }
    }

    TextArea
    {
        id: bigNumber2
        width: bigIntCalculator.width / 5 * 4
        height: bigIntCalculator.height / 10 * 3
        anchors.top: bigNumber1.bottom
        anchors.left: bigIntCalculator.left
        wrapMode: TextEdit.Wrap

        onTextChanged:
        {
            if(text.length > 1 && text.charAt(0) === '0')
            {
                remove(0, 1)
                cursorPosition = 1
            }
        }

        function setBigNumber2ToCPP()
        {
            bigIntNumbersBases.bigNumber2 = bigNumber2.text
        }
    }

    Text
    {
        id: textOutputBase
        text: "output base:"
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: bigNumber2.bottom
        anchors.left: bigIntCalculator.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Button
    {
        id: baseOutputBinary
        enabled: bigIntNumbersBases.baseOutput != 2
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textOutputBase.top
        anchors.left: textOutputBase.right

        text: "bin"
        onClicked:
        {
            bigIntNumbersBases.baseOutput = 2
        }
    }

    Button
    {
        id: baseOutputDecimal
        enabled: bigIntNumbersBases.baseOutput != 10
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textOutputBase.top
        anchors.left: baseOutputBinary.right

        text: "dec"
        onClicked:
        {
            bigIntNumbersBases.baseOutput = 10
        }
    }

    Button
    {
        id: baseOutputHexadecimal
        enabled: bigIntNumbersBases.baseOutput != 16
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.top: textOutputBase.top
        anchors.left: baseOutputDecimal.right

        text: "hex"
        onClicked:
        {
            bigIntNumbersBases.baseOutput = 16
        }
    }

    TextArea
    {
        id: calculationsResult
        readOnly: true
        width: bigIntCalculator.width / 5 * 4
        height: bigIntCalculator.height / 10 * 3
        anchors.top: textOutputBase.bottom
        anchors.left: bigIntCalculator.left
        wrapMode: TextEdit.Wrap

        function getCalculationsResultFromCPP()
        {
            calculationsResult.text = bigIntNumbersBases.calculationsResult
        }
    }

    Grid
    {
        id: buttonGrid
        columns: 2
        anchors.top: bigIntCalculator.top
        anchors.left: calculationsResult.right

        property real buttonWidth: bigIntCalculator.width / 10
        property real buttonHeight: bigIntCalculator.height / 10

        Button { text: "+"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "-"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "*"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "/"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { if(bigNumber2.text !== "0") { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() }
                         else { calculationsResult.text = "Divide by zero exception" } } }
        Button { text: "%"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { if(bigNumber2.text !== "0") { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() }
                         else { calculationsResult.text = "Divide by zero exception" } } }
        Button { text: "pow"; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "~"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length === 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "&&" ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "|"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "^"  ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "<<" ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: ">>" ; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "gcd"; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
        Button { text: "lcm"; width: buttonGrid.buttonWidth; height: buttonGrid.buttonHeight; enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
            onClicked: { bigNumber1.setBigNumber1ToCPP(); bigNumber2.setBigNumber2ToCPP(); bigIntNumbersBases.calculate(text); calculationsResult.getCalculationsResultFromCPP() } }
    }

    Button
    {
        id: clear
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.bottom: buttonMenu.top
        anchors.left: calculationsResult.right

        text: "clear"
        onClicked:
        {
            bigNumber1.text = ""
            bigNumber2.text = ""
            calculationsResult.text = ""

        }
    }

    Loader
    {
        id: menuLoader
    }

    Button
    {
        id: buttonMenu
        width: bigIntCalculator.width / 5
        height: bigIntCalculator.height / 20
        anchors.bottom: calculationsResult.bottom
        anchors.left: calculationsResult.right

        text: "menu"
        onClicked: {
            menuLoader.source = ""
            menuLoader.source = "../main.qml"
            bigIntCalculator.close()
        }
    }
}
