import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root
    anchors.fill: parent
    property alias motivationValue: motivationInputId.text
    property alias priorityValue: priorityInputId.text

    function clearData() {
        console.log("RC: Clearing data");
        motivationInputId.text = "";
        priorityInputId.text = "";
    }

    function validateInput()
    {
        if(motivationInputId.text != "" && priorityInputId.text != "")
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

    Label
    {
        id: priorityLabelId
        text: "Priority: "
        color: "black"
        anchors.left: parent.left
        anchors.verticalCenter: priorityInputId.verticalCenter
    }

    TextField {
        id: priorityInputId
        maximumLength: 4
        anchors.left: motivationInputId.left
        anchors.top: motivationInputId.bottom
        anchors.topMargin: 10

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
}

















