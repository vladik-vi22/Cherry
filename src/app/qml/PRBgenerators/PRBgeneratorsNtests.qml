import QtQuick
import QtQuick.Controls
import QtQuick.Window

import PRBgenerators 1.0

ApplicationWindow
{
    id: prbGenerators
    visible: true
    width: Screen.width / 3
    height: Screen.height / 2
    title: qsTr("PRB Generators & Tests")

    PRBgenerators
    {
        id: prbGeneratorsNtests
    }

    ComboBox
    {
        id: prbGeneratorsSelector
        width: prbGenerators.width / 2
        model: ["Built-in CPP (bit)", "Built-in CPP (byte)", "Lehmer Low", "Lehmer High", "L20", "L89", "Geffe", "Wolfram", "Librarian", "Blum-Micali (bit)", "Blum-Micali (byte)", "Blum Blum Shub (bit)", "Blum Blum Shub (byte)"]
        onCurrentIndexChanged:
        {
            generatedPRBS.text = ""
            resultTestOfGoodnessOfFit.text = ""
            resultTestOfHomogeneity.text = ""
            resultTestIndependence.text = ""
        }
    }

    TextArea
    {
        id: generatedPRBS
        readOnly: true
        width: prbGenerators.width / 2
        height: prbGenerators.height
        anchors.right: parent.right
        wrapMode: TextEdit.Wrap
    }

    Text
    {
        id: textNumberOfBits
        text: qsTr("number of bit =")
        width: prbGenerators.width / 4
        height: numberOfBits.height
        anchors.top: prbGeneratorsSelector.bottom
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    TextField
    {
        id: numberOfBits
        width: prbGenerators.width / 4
        anchors.top: prbGeneratorsSelector.bottom
        anchors.left: textNumberOfBits.right

        function setNumberOfBitsToCPP()
        {
            prbGeneratorsNtests.numberOfBits = numberOfBits.text
        }
    }

    Button
    {
        id: generate
        enabled: numberOfBits.length != 0
        text: qsTr("generate")
        width:prbGenerators.width / 2
        anchors.top: numberOfBits.bottom

        onClicked:
        {
            numberOfBits.setNumberOfBitsToCPP()
            switch(prbGeneratorsSelector.currentIndex)
            {
            case 0:
                prbGeneratorsNtests.generateBuiltInCPPBit()
                break
            case 1:
                prbGeneratorsNtests.generateBuiltInCPPByte()
                break
            case 2:
                prbGeneratorsNtests.generateLehmerLow()
                break
            case 3:
                prbGeneratorsNtests.generateLehmerHigh()
                break
            case 4:
                prbGeneratorsNtests.generateL20()
                break
            case 5:
                prbGeneratorsNtests.generateL89()
                break
            case 6:
                prbGeneratorsNtests.generateGeffe()
                break
            case 7:
                prbGeneratorsNtests.generateWolfram()
                break
            case 8:
                prbGeneratorsNtests.generateLibrarian()
                break
            case 9:
                prbGeneratorsNtests.generateBlumMicaliBit()
                break
            case 10:
                prbGeneratorsNtests.generateBlumMicaliByte()
                break
            case 11:
                prbGeneratorsNtests.generateBlumBlumShubBit()
                break
            case 12:
                prbGeneratorsNtests.generateBlumBlumShubByte()
                break
            }
            generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
        }
    }

    Text
    {
        id: textAlpha
        text: qsTr("alpha =")
        width: prbGenerators.width / 4
        height: alpha.height
        anchors.top: generate.bottom
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    TextField
    {
        id: alpha
        placeholderText: qsTr("0.01 - 0.1")
        width: prbGenerators.width / 4
        anchors.top: generate.bottom
        anchors.left: textAlpha.right

        function setAlphaToCPP()
        {
            prbGeneratorsNtests.alpha = alpha.text
        }
    }

    Button
    {
        id: testOfGoodnessOfFit
        enabled: alpha.length != 0 && generatedPRBS.length != 0
        text: qsTr("test of Goodness Of Fit")
        width:prbGenerators.width / 2
        anchors.top: alpha.bottom

        onClicked:
        {
            alpha.setAlphaToCPP()
            resultTestOfGoodnessOfFit.text = prbGeneratorsNtests.testOfGoodnessOfFit() ? "test passed" : "test failed"
            resultTestOfGoodnessOfFit.textColor = prbGeneratorsNtests.testOfGoodnessOfFit() ? "green" : "red"
        }
    }

    TextField
    {
        id: resultTestOfGoodnessOfFit
        readOnly: true
        width: prbGenerators.width / 2
        height: testOfGoodnessOfFit.height
        horizontalAlignment: Text.AlignHCenter
        anchors.top: testOfGoodnessOfFit.bottom
    }

    Text
    {
        id: textNumberOfSegments
        text: qsTr("number of segment =")
        width: prbGenerators.width / 4
        height: numberOfSegments.height
        anchors.top: resultTestOfGoodnessOfFit.bottom
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    TextField
    {
        id: numberOfSegments
        width: prbGenerators.width / 4
        anchors.top: resultTestOfGoodnessOfFit.bottom
        anchors.left: textNumberOfSegments.right

        function setNumberOfSegmentsToCPP()
        {
            prbGeneratorsNtests.numberOfSegments = numberOfSegments.text
        }
    }

    Button
    {
        id: testOfHomogeneity
        enabled: alpha.length != 0 && generatedPRBS.length != 0 && numberOfSegments.length != 0
        text: qsTr("test of Homogeneity")
        width:prbGenerators.width / 2
        anchors.top: numberOfSegments.bottom

        onClicked:
        {
            alpha.setAlphaToCPP()
            numberOfSegments.setNumberOfSegmentsToCPP()
            resultTestOfHomogeneity.text = prbGeneratorsNtests.testOfHomogeneity() ? "test passed" : "test failed"
            resultTestOfHomogeneity.textColor = prbGeneratorsNtests.testOfHomogeneity() ? "green" : "red"
        }
    }

    TextField
    {
        id: resultTestOfHomogeneity
        readOnly: true
        width: prbGenerators.width / 2
        height: testOfHomogeneity.height
        horizontalAlignment: Text.AlignHCenter
        anchors.top: testOfHomogeneity.bottom
    }

    Button
    {
        id: testOfIndependence
        enabled: alpha.length != 0 && generatedPRBS.length != 0
        text: qsTr("test of Independence")
        width:prbGenerators.width / 2
        anchors.top: resultTestOfHomogeneity.bottom

        onClicked:
        {
            alpha.setAlphaToCPP()
            resultTestIndependence.text = prbGeneratorsNtests.testOfIndependence() ? "test passed" : "test failed"
            resultTestIndependence.textColor = prbGeneratorsNtests.testOfIndependence() ? "green" : "red"
        }
    }

    TextField
    {
        id: resultTestIndependence
        readOnly: true
        width: prbGenerators.width / 2
        height: testOfIndependence.height
        horizontalAlignment: Text.AlignHCenter
        anchors.top: testOfIndependence.bottom
    }

    Button
    {
        id: clear
        width: prbGenerators.width / 2
        anchors.bottom: buttonMenu.top

        text: "clear"
        onClicked:
        {
            generatedPRBS.text = ""
            numberOfBits.text = ""
            alpha.text = ""
            resultTestOfGoodnessOfFit.text = ""
            resultTestOfHomogeneity.text = ""
            resultTestIndependence.text = ""
            prbGeneratorsSelector.currentIndex = 0
        }
    }

    Loader
    {
        id: menuLoader
    }

    Button
    {
        id: buttonMenu
        width: prbGenerators.width / 2
        anchors.bottom: parent.bottom

        text: "menu"
        onClicked: {
            menuLoader.source = ""
            menuLoader.source = "../main.qml"
            prbGenerators.close()
        }
    }

}
