import QtQuick 2.0
import QtQuick.Controls 1.2
import PRBgenerators 1.0

ApplicationWindow
{
    id: prbGenerators
    visible: true
    width: parent.width
    height: parent.height
    title: qsTr("PRB Generators & Tests")

    PRBgenerators
    {
        id: prbGeneratorsNtests
    }

    ComboBox
    {
        id: prbGeneratorsSelector
        width: prbGenerators.width / 2
        model: ["Built-in CPP", "Lehmer Low", "Lehmer High", "L20", "L89", "Geffe", "Wolfram", "Librarian", "Blum-Micali (bit)", "Blum-Micali (byte)", "Blum Blum Shub (bit)", "Blum Blum Shub (byte)"]
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
        id: textNumberOfBit
        text: qsTr(" number of bit = ")
        width: prbGenerators.width / 4
        height: numberOfBit.height
        anchors.top: prbGeneratorsSelector.bottom
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    TextField
    {
        id: numberOfBit
        width: prbGenerators.width / 4
        anchors.top: prbGeneratorsSelector.bottom
        anchors.left: textNumberOfBit.right

        function setNumberOfBitToCPP()
        {
            prbGeneratorsNtests.numberOfBit = numberOfBit.text
        }
    }

    Button
    {
        id: generate
        enabled: numberOfBit.length != 0
        text: qsTr("generate")
        width:prbGenerators.width / 2
        anchors.top: numberOfBit.bottom

        onClicked:
        {
            switch(prbGeneratorsSelector.currentIndex)
            {
            case 0:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateBuiltInCPP()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 1:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateLehmerLow()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 2:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateLehmerHigh()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 3:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateL20()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 4:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateL89()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 5:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateGeffe()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 6:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateWolfram()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 7:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateLibrarian()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 8:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateBlumMicaliBit()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 9:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateBlumMicaliByte()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 10:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateBlumBlumShubBit()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            case 11:
                numberOfBit.setNumberOfBitToCPP()
                prbGeneratorsNtests.generateBlumBlumShubByte()
                generatedPRBS.text = prbGeneratorsNtests.getQStringGeneratedPRBS()
                break
            }
        }
    }

    Text
    {
        id: textAlpha
        text: qsTr(" alpha = ")
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

    Button
    {
        id: testOfHomogeneity
        enabled: alpha.length != 0 && generatedPRBS.length != 0
        text: qsTr("test of Homogeneity")
        width:prbGenerators.width / 2
        anchors.top: resultTestOfGoodnessOfFit.bottom

        onClicked:
        {
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
            numberOfBit.text = ""
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
