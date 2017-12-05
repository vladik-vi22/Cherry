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
        width: prbGenerators.width / 4
        height: prbGenerators.height / 20
        model: ["Built-in CPP", "Lehmer Low", "Lehmer High", "L20", "L89", "Geffe", "Wolfram", "Librarian", "Blum-Micali (bit)", "Blum-Micali (byte)", "Blum Blum Shub (bit)", "Blum Blum Shub (byte)"]
    }

}
