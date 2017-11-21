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

        function setBigNum1ToCPP()
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

        function setBigNum2ToCPP()
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



}



