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

    Text
    {
        id: textGenerate
        text: qsTr("Generate")
        width: prbGenerators.width / 15 * 2
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textTest
        text: qsTr("bit;    Test :")
        width: prbGenerators.width / 15 * 2
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: numberOfBit.right
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    TextField
    {
        id: numberOfBit
        width: prbGenerators.width / 15 * 2
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: textGenerate.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textEquiprobability
        text: qsTr("GoodnessOfFit")
        width: prbGenerators.width / 5
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: textTest.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textIndependence
        text: qsTr("Homogeneity")
        width: prbGenerators.width / 5
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: textEquiprobability.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textHomogeneity
        text: qsTr("Independence")
        width: prbGenerators.width / 5
        height: prbGenerators.height / 15
        anchors.top: prbGenerators.top
        anchors.left: textIndependence.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textBuilInCPP
        text: qsTr("Built-inCPP")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: numberOfBit.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textLehmerLow
        text: qsTr("LehmerLow")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textBuilInCPP.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textLehmerHigh
        text: qsTr("LehmerHigh")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textLehmerLow.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textL20
        text: qsTr("L20")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textLehmerHigh.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textL89
        text: qsTr("L89")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textL20.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textGeffe
        text: qsTr("Geffe")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textL89.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textWolfram
        text: qsTr("Wolfram")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textGeffe.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textLibrarian
        text: qsTr("Librarian")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textWolfram.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textBlumMikaliBit
        text: qsTr("BlumMikaliBit")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textLibrarian.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textBlumMikaliByte
        text: qsTr("BlumMikaliByte")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textBlumMikaliBit.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textBlumBlumShubBit
        text: qsTr("BlumBlumShubBit")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textBlumMikaliByte.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text
    {
        id: textBlumBlumShubByte
        text: qsTr("BlumBlumShubByte")
        width: prbGenerators.width / 4
        height: prbGenerators.height / 15
        anchors.top: textBlumBlumShubBit.bottom
        anchors.left: prbGenerators.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }


}
