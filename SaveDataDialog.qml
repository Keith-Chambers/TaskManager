import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQml.Models 2.1

Dialog
{
    id: saveDataDialog
    visible: true
    title: "Save Data Confirmation"
    modality: Qt.ApplicationModal

    contentItem: Rectangle
    {
        implicitHeight: 100
        implicitWidth: 300
        color: "lightgrey"

        Text
        {
            text: "Do you wish to save current session data?"
            color: "Black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top;
            anchors.topMargin: 20
        }

        Rectangle
        {
            id: yesButton
            height: 30
            width: 80
            color: "lightblue"
            anchors.right: noButton.left
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            border.color: "black"
            border.width: 1
            radius: 3

            Text
            {
                text: "Yes"
                color: "Black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    console.log("Clicked");
                }
            }
        }

        Rectangle
        {
            id: noButton
            height: 30
            width: 80
            color: "lightblue"
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            border.color: "black"
            border.width: 1
            radius: 3

            Text
            {
                text: "No"
                color: "Black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    console.log("Clicked");
                }
            }
        }
    }
}
