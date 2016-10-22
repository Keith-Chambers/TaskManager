import QtQuick 2.0
import QtQuick.Dialogs 1.2
import kdc.pane 1.0

Dialog
{
    id: root
    title: "Add GoalView to Pane"
    visible: false
    // Invalid value
    property int targetPaneId: -1
    signal selectionComplete;

    onVisibleChanged:
    {
        if(visible == true)
        {
            console.log("Target Pane = " + targetPaneId)
            Tasks.loadTasksToContextIfGoalView();
            Tasks.clearGoalViewContext();
        }
    }

    contentItem: Rectangle
    {
        id: listViewContainer
        implicitHeight: 450
        implicitWidth: 400
        color: "lightblue"
        border.width: 1
        border.color: "Black"

        property int currentTaskId: -1
        property int currentGoalViewId: -1
        function newTaskId(taskId)
        {
            currentTaskId = taskId;
            console.log("Loading goalViews from task Id " + taskId);
            if(currentTaskId != -1)
            { Tasks.loadGoalViewsToContext(currentTaskId); }
        }


        ListView
        {
            id: taskList
            model: TaskModel
            height: 400
            width: 350
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1

            delegate: Item
            {
                id: taskDelegateContainer
                height: childrenRect.height
                anchors
                {
                    left: parent.left
                    right: parent.right
                }

                Rectangle
                {
                    id: taskDelegate
                    anchors
                    {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }
                    height: 50
                    color: "lightgrey"
                    border.width: 1
                    border.color: "Black"

                    Text
                    {
                        text: model.modelData.name
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            console.log("Clicked");
                            taskList.currentIndex = index;
                            listViewContainer.newTaskId(model.modelData.taskId);
                        }
                    }
                }

                ListView
                {
                    id: goalList
                    model: taskList.currentIndex == index ? goalViewModel : 0
                    anchors
                    {
                        left: parent.left
                        right: parent.right
                        top: taskDelegate.bottom
                        topMargin: 1
                    }
                    height: count * 40
                    spacing: 1

                    delegate: Rectangle
                    {
                        id: goalViewDelegate
                        anchors
                        {
                            left: parent.left
                            right: parent.right
                        }
                        height: 40
                        color: goalList.currentIndex == index ? "blue" : "white"
                        border.width: 1
                        border.color: "Black"

                        Text
                        {
                            id: goalViewText
                            anchors.centerIn: parent
                            text: model.modelData.daysLeft
                        }

                        MouseArea
                        {
                            id: goalViewMouse
                            anchors.fill: parent
                            onClicked:
                            {
                                if(goalList.model == 0)
                                {
                                    console.log("Empty GoalView model");
                                    return;
                                }

                                goalList.currentIndex = index;
                                // Remove this gobal var if not needed in the future
                                listViewContainer.currentGoalViewId = model.modelData.goalId;

                                var goalViewId = listViewContainer.currentGoalViewId;
                                console.log("GoalViewId : " + goalViewId);
                                var taskId = listViewContainer.currentTaskId;
                                console.log("TaskId : " + taskId);
                                var pane = PaneManager.find(targetPaneId);
                                var goalView = Tasks.getGoalView(taskId, goalViewId);

                                if(pane == null || goalView == null)
                                {
                                    console.log("Failed to get pane and/or goalView for assignment");
                                    return;
                                }

                                if(pane.addGoalView(goalView) == false)
                                {
                                    console.log("A problem occurred while try to add goalView to pane");
                                    return;
                                }

                                console.log("GoalView successfully added to pane");
                                selectionComplete();
                            }
                        }
                    }
                } // End goalList
            } // End taskDelegateContainer
        } // End taskList

/*
        Item
        {
            id: controlButtons
            anchors
            {
                horizontalCenter: parent.horizontalCenter
                top: taskList.bottom
                topMargin: 10
            }

            height: childrenRect.height
            width: childrenRect.width + 10

            Rectangle
            {
                id: createButton
                width: 100
                height: 30
                anchors.right: parent.right
                anchors.top: parent.top
            }

            Rectangle
            {
                id: returnButton
                width: 100
                height: 30
                anchors.left: parent.left
                anchors.top: parent.top
            }

        }
        */

    } // End listViewContainer
}
