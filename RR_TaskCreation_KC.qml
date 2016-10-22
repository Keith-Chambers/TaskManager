import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root
    anchors.fill: parent

    property alias motivationValue: motivationInputId.text

    function clearData() {
        console.log("RR: Clearing data");
        motivationInputId.text = "";
    }

    function validateInput()
    {
        if(motivationInputId.text != "")
        {
            return true;
        }else
        {
            return false;
        }
    }

    Label
    {
        id: motivationLabelId
        anchors.left: parent.left
        anchors.verticalCenter: motivationInputId.verticalCenter
        text: "Motivation: "
        color: "black"
    }

    TextField {
        id: motivationInputId
        maximumLength: 4
        anchors.left: motivationLabelId.right
        anchors.leftMargin: 10
        anchors.top: parent.top

        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: 40
                implicitHeight: 24
                border.color: "#333"
                border.width: 1
            }
        }
    }

    Rectangle
    {
        id: goalViewButton
        height: 25
        width: 150
        color: "lightblue"
        border.color: "black"
        border.width: 1
        radius: 5
        anchors.left: motivationInputId.right
        anchors.leftMargin: 20
        anchors.top: parent.top

        Label
        {
            anchors.centerIn: parent
            id: goalViewLabel
            text: "Create Goal Views"
            color: "Black"
        }

        MouseArea
        {
            id: goalViewMouseAreaId
            anchors.fill: parent
            onClicked: console.log("Clicked")
        }
    }
}
