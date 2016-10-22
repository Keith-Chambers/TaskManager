import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4


Dialog {

    id: createCatDialog
    visible: false
    title: "Create New Catagory"

    onVisibilityChanged: clearDialogData();

    function clearDialogData()
    {
        nameTextAreaId.text = "";
        descTextAreaId.text = "";
    }

    contentItem: Rectangle {
        color: "lightgrey"
        implicitWidth: 400
        implicitHeight: 250

        Label
        {
            id: nameLabel
            text: "Name: "
            color: "black"
            font.bold: true
            anchors.verticalCenter: nameTextAreaId.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
        }

        TextArea
        {
            id: nameTextAreaId
            wrapMode: TextEdit.WrapAnywhere
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: nameLabel.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 30
            height: nameLabel.height + 10

            style:
                TextAreaStyle
                {
                    backgroundColor: "white"
                    textColor: "black"
                }
        }

        Label
        {
            id: descLabel
            text: "Desc: "
            color: "black"
            font.bold: true
            anchors.verticalCenter: descTextAreaId.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
        }

        TextArea
        {
            id: descTextAreaId
            wrapMode: TextEdit.WrapAnywhere
            anchors.top: nameTextAreaId.top
            anchors.topMargin: 30
            anchors.left: nameLabel.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: createCatagoryButtonRect.top
            anchors.bottomMargin: 10

            style:
                TextAreaStyle
                {
                    backgroundColor: "white"
                    textColor: "black"
                }
        }

        Rectangle
        {
            id: createCatagoryButtonRect
            anchors
            {
                left: descTextAreaId.left
                right: descTextAreaId.right
                bottom: parent.bottom
                bottomMargin: 10
            }
            height: 30
            color: "lightblue"
            border.width: 1
            border.color: "black"
            radius: 3

            Label
            {
                id: createCatagoryButtonLabel
                text: "Create Catagory"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: createCatagoryButtonMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Creating new catagory");
                    TaskManager.addCatagory(nameTextAreaId.text, descTextAreaId.text);
                    createCatDialog.clearDialogData();
                    createCatDialog.close();
                }
            }
        }
    }
}

