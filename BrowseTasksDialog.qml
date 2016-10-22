import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQml.Models 2.1

Dialog
{
    id: browseTaskDialog
    visible: false
    title: "Browse Tasks"

    contentItem: Rectangle
    {
        id: root
        implicitHeight: 400
        implicitWidth: 250
        color: "lightgrey"

        Item
        {
            id: topOptions
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            Rectangle
            {
                id: deleteRect
                height: parent.height
                width: parent.width / 3 - 2
                anchors.left: parent.left
                anchors.top: parent.top
                color: "Red"
                border.width: 1
                border.color: "Black"

                Text
                {
                    id: deleteText
                    text: "Delete"
                    color: "Black"
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent
                    id: deleteMouse
                    onClicked: {
                        console.log("Clicked")
                        //TaskManager.deleteTask(delegateRect.items.get(currentIndex).model.modelData.taskType,
                          //                     delegateRect.items.get(currentIndex).model.modelData.taskId);
                    }

                }
            }

            Rectangle
            {
                id: archieveRect
                height: parent.height
                width: root.width / 3 - 2
                anchors.left: deleteRect.right
                anchors.top: parent.top
                color: "Blue"
                border.width: 1
                border.color: "Black"

                Text
                {
                    id: archieveText
                    text: "Archieve"
                    color: "Black"
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent
                    id: archieveMouse
                    onClicked: console.log("Clicked")
                }
            }

            Rectangle
            {
                id: editRect
                height: parent.height
                width: root.width / 3 - 2
                anchors.left: archieveRect.right
                // anchors.right: parent.right
                anchors.top: parent.top
                color: "green"
                border.width: 1
                border.color: "Black"

                Text
                {
                    id: editText
                    text: "Edit"
                    color: "Black"
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent
                    id: editMouse
                    onClicked: console.log("Clicked")
                }
            }
        }

        ListView
        {
            id: browseTaskListView
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 1
            clip: true
            model: TaskModel
            focus: true

            delegate: Rectangle
            {
                id: delegateRect
                height: 40

                width: browseTaskListView.width
                radius: 3
                border.width: 1
                border.color: "black"
                color: if(browseTaskListView.currentIndex == index) return "darkblue"; else return "skyblue";

                Text
                {
                    anchors.centerIn: parent
                    text: model.modelData.name;
                    color: "black"
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        browseTaskListView.currentIndex = index
                    }
                }
            }

            highlight: Rectangle
            {
                height: 40
                width: browseTaskListView.width
                color: "red"
            }
        }
    }
}
