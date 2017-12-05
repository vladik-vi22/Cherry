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
        anchors.top: prbGenerators.title
        width: prbGenerators.width / 2
        currentIndex: 1
        model: ["1" , "2" , "3"]

    }

}
