import QtQuick 2.0
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

    Button
    {
        id: addition
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bigIntCalculator.top
        anchors.left: calculationsResult.right

        text: "+"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(addition.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: subtraction
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bigIntCalculator.top
        anchors.left: addition.right

        text: "-"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(subtraction.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: multiplication
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: addition.bottom
        anchors.left: calculationsResult.right

        text: "*"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(multiplication.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: division
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: subtraction.bottom
        anchors.left: multiplication.right

        text: "/"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(division.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: modulo
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: multiplication.bottom
        anchors.left: calculationsResult.right

        text: "%"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(modulo.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: power
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: division.bottom
        anchors.left: modulo.right

        text: "pow"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(power.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseNOT
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length === 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: modulo.bottom
        anchors.left: calculationsResult.right

        text: "~"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseNOT.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseAND
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: power.bottom
        anchors.left: bitwiseNOT.right

        text: "&&"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseAND.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseOR
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseNOT.bottom
        anchors.left: calculationsResult.right

        text: "|"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseOR.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseXOR
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseAND.bottom
        anchors.left: bitwiseOR.right

        text: "^"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseXOR.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseLeftShift
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseOR.bottom
        anchors.left: calculationsResult.right

        text: "<<"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseLeftShift.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: bitwiseRightShift
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseXOR.bottom
        anchors.left: bitwiseLeftShift.right

        text: ">>"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(bitwiseRightShift.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: gcd
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseLeftShift.bottom
        anchors.left: calculationsResult.right

        text: "gcd"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(gcd.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
    }

    Button
    {
        id: lcm
        enabled: bigNumber1.text.length !== 0 && bigNumber2.text.length !== 0
        width: bigIntCalculator.width / 10
        height: bigIntCalculator.height / 10
        anchors.top: bitwiseRightShift.bottom
        anchors.left: gcd.right

        text: "lcm"
        onClicked:
        {
            bigNumber1.setBigNumber1ToCPP()
            bigNumber2.setBigNumber2ToCPP()
            bigIntNumbersBases.calculate(lcm.text)
            calculationsResult.getCalculationsResultFromCPP()
        }
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



