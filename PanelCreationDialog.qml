import QtQuick 2.0
import QtQuick.Dialogs 1.2
import kdc.pane 1.0
import kdc.date 1.0

Dialog {
    id: root
    title: "Create New Panel"
    signal quit;

    contentItem: Rectangle
    {
        id: contentRect
        implicitHeight: 250
        implicitWidth: 350

        Text
        {
            id: heading
            text: "Enter End Date for Pane"
            anchors
            {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                topMargin: 5
            }
            //height: 10
        }

        SelectYear_KC
        {
            id: dateId
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: heading.bottom
            anchors.topMargin: 10
        }

        Rectangle
        {
            id: createGoalView

            height: 30
            width: 100
            color: "lightblue"
            border.width: 1
            border.color: "Black"
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: dateId.bottom
            anchors.topMargin: 20

            Text
            {
                id: createText
                text: "Create"
                color: "Black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: createMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Doing things..")
                    var endDate = new Date(dateId.year, dateId.month, dateId.day);
                    if(PaneManager.addPane(endDate) == false)
                    {
                        console.log("Failed to add pane");
                        return;
                    }
                }
            }
        }

        Rectangle
        {
            id: cancelButton

            height: 30
            width: 100
            color: "lightblue"
            border.width: 1
            border.color: "Black"
            anchors.right: createGoalView.left
            anchors.rightMargin: 10
            anchors.top: createGoalView.top

            Text
            {
                id: cancelText
                text: "Cancel"
                color: "Black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: cancelMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Quitting");
                    quit();
                }
            }
        }
    }
}
