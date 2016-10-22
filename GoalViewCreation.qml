import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import kdc.date 1.0;
import kdc.goalView 1.0

Rectangle {
    id: root
    height: 250
    width: 350
    border.width: 1
    border.color: "black"

    property int taskId: 0
    signal quit;

    function clearData()
    {
        timeId.clearData();
        dateId.clearData();

        goalProgressInput.text = "";

    }

    SelectTime_KC
    {
        id: timeId
        anchors.left: parent.left;
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    SelectYear_KC
    {
        id: dateId
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Item
    {
        id: goalProgress
        anchors.top: dateId.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        height: childrenRect.height

        Text
        {
            id: goalProgressText
            text: "GoalProgess(Hours/Items) "
            color: "Black"
            font.bold: true
            anchors.left: parent.left
            anchors.verticalCenter: goalProgressInput.verticalCenter
        }

        TextField
        {
            id: goalProgressInput
            anchors.top: parent.top
            anchors.left: goalProgressText.right
            anchors.leftMargin: 10

            style: TextFieldStyle {
                textColor: "black"

                background: Rectangle {
                    radius: 2
                    implicitWidth: 100
                    implicitHeight: 24
                    border.color: "#333"
                    border.width: 1
                }
            }
        }
    }

    Item
    {
        id: controlButtons

        anchors
        {
            top: goalProgress.bottom
            topMargin: 15
            left: parent.left
            leftMargin: 20
            right: parent.right
            rightMargin: 20
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
            anchors.top: parent.top

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
                    var date = KDate;
                    var goalView = GoalView;

                    if(date.setDate(dateId.year, dateId.month, dateId.day, timeId.hour, timeId.minute, timeId.second) &&
                            root.taskId > 0)
                    {
                        goalView.initialize(Number(goalProgressText.text), taskId, date);
                        if(false == Tasks.addGoalView(goalView)){ return; }
                        clearData();
                    }else
                    {
                        console.log("Failed to add goalView");
                        console.log(root.taskId)
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
            anchors.top: parent.top

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
