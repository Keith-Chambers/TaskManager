import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: browseTasks

    anchors
    {
        fill: parent
    }

    function reset()
    {
        browseCatListView.currentIndex = 0;
    }

    property int currentTaskId: -1

    ListView
    {
        id: browseCatListView
        anchors
        {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: 200

        spacing: 1
        clip: true
        model: CatagoriesModel
        focus: true


        property int currentCatId:
        {
            console.log("Current Index: " + currentIndex);
            if(currentIndex == -1 || count <= 0) return -1; else return currentItem.myCatData.modelData.id;
        }


        delegate: Rectangle
        {
            id: delegateRect
            height: 40
            property variant myCatData: model

            width: browseCatListView.width
            radius: 3
            border.width: 1
            border.color: "black"
            color: "skyblue"

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
                    console.log("Clicked");
                    browseCatListView.currentIndex = index
                    taskFlow.updateTasks(model.modelData.id);
                    //TaskManager.loadTaskContextByCatagory(model.modelData.id);
                }
            }
        }
    }

    GridView
    {
        id: taskFlow
        anchors.left: browseCatListView.right
        anchors.top: menuBarRect.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 30
        anchors.rightMargin: 10
        cellHeight: 120
        cellWidth: 120

        signal updateTasks(int catId)
        property int currentTaskType:
        {
            console.log("Current Task Index: " + currentIndex);
            if(currentIndex != -1 && count > 0) return currentItem.myData.taskType; else return -1;
        }
        property int currentTaskId: if(currentIndex != -1 && count > 0) return currentItem.myData.taskId; else return -1;

        onUpdateTasks:
        {
            console.log("Updating Tasks");
            console.log("CatID: "  + catId);
            TaskManager.loadTaskContextByCatagory(catId);
        }

        model: TaskModel
        delegate: Rectangle
        {
            id: taskDelegate
            property variant myData: if(taskFlow.count > 0) return model; else return NULL;
            width: 100
            height: 100
            border.width: 1
            border.color: "Black"
            color: if(index == taskFlow.currentIndex){ return "lightblue"; }else {return "lightgrey"; }
            radius: 2

            Text
            {
                text: model.modelData.name
                color: "black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: taskMouseArea
                anchors.fill: parent

                function updateTaskId()
                {
                    currentTaskId = model.modelData.taskId;
                    console.log(currentTaskId);
                }

                onClicked:
                {
                    taskFlow.currentIndex = index
                    updateTaskId();
                }
            }
        }
    }

    Rectangle
    {
        id: menuBarRect
        anchors.left: browseCatListView.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.rightMargin: 5
        height: 30
        color: "darkgrey"

        Rectangle
        {
            id: deleteOpt
            height: parent.height - 4
            width: 100
            color: "blue"
            border.width: 1
            border.color: "Black"
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 5
            }

            Text
            {
                text: "Delete"
                color: "white"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: deleteMouse
                anchors.fill: parent

                onClicked:
                {
                    var id = taskFlow.currentTaskId;
                    var type = taskFlow.currentTaskType;
                    console.log("Deleting task");

                    if(Tasks.deleteTask(id) == true)
                    {
                        console.log("Task deleted");
                        console.log("Loading tasks to context");
                        taskFlow.updateTasks(browseCatListView.currentCatId);
                    }else
                    {
                        console.log("Failed to delete task");
                    }
                }
            }
        }

        Rectangle
        {
            id: archieveOpt
            height: parent.height - 4
            width: 100
            border.width: 1
            border.color: "Black"
            color: "blue"
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: deleteOpt.right
                leftMargin: 5
            }

            Text
            {
                text: "Archieve"
                color: "white"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: archieveMouse
                anchors.fill: parent
                onClicked:
                {
                    var id = taskFlow.currentTaskId;

                    if(Tasks.archieveTask(id) == true)
                    {
                        console.log("Task archeived");
                        taskFlow.updateTasks(browseCatListView.currentCatId);
                    }else
                    {
                        console.log("Failed to archieve task");
                    }
                }
            }
        }

        Rectangle
        {
            id: editOpt
            height: parent.height - 4
            width: 100
            border.width: 1
            border.color: "Black"
            color: "blue"
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: archieveOpt.right
                leftMargin: 5
            }

            Text
            {
                text: "Edit"
                color: "white"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: editMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Edit Clicked");
                    // Workout how the date object contructor works..
                    //TaskManager.addGoalView(new Date(1, 3, 3, 1));
                    // ? Month ? day
                }
            }
        }

        Rectangle
        {
            id: createGoalViewOpt
            height: parent.height - 4
            width: 100
            border.width: 1
            border.color: "Black"
            color: "blue"
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: editOpt.right
                leftMargin: 5
            }

            Text
            {
                text: "New GoalView"
                color: "white"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: goalViewMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Clicked");
                    createGoalViewDialog.visible = true
                }
            }
        }
    }

    Dialog
    {
        id: createGoalViewDialog
        visible: false
        title: "Create GoalView"

        contentItem: GoalViewCreation
        {
            id: goalViewCreation
            implicitHeight: goalViewCreation.height
            implicitWidth: goalViewCreation.width
            taskId: currentTaskId
            onQuit:
            {
                clearData();
                createGoalViewDialog.close();
            }
        }
    }
}
