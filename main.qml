import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import kdc.date 1.0;

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    minimumHeight: 450
    minimumWidth: 550
    maximumHeight: 550
    maximumWidth: 700

    function hideMenuBar()
    {
        manageCatagoriesMenu.visible = false;
        createTaskMenu.visible = false;
    }

    function showMenuBar()
    {
        manageCatagoriesMenu.visible = true;
        createTaskMenu.visible = true;
    }

    Action
    {
        id: hideClearButton
        shortcut: "Ctrl+H"
        onTriggered:
        {
            console.log("Key pressed");
            clearButton.visible = !clearButton.visible;
        }
    }

    Rectangle
    {
        id: clearButton
        height: 100;
        width: 150;
        color: "lightblue"
        anchors.centerIn: parent
        border.width: 1
        border.color: "black"
        radius: 2
        visible: false

        Text
        {
            text: "Clear Data"
            color: "black"
            anchors.centerIn: parent
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                parent.visible = false;
                TaskManager.clearData();

                //goalViewCreation.visible = true;
            }
        }
    }

    GoalViewPane
    {
        id: goalViewPane
        visible: true
    }

    PanelCreationDialog
    {
        id: panelCreation
        visible: false;
        onQuit: visible = false;
    }


    menuBar: MenuBar
    {
        id: topBar

        function clearAll()
        {
            browseTasks.visible = false;
            browseTasks.reset();
        }

        Menu
        {
            id: createTaskMenu
            title: "Create Task"
            MenuItem
            {
                text: "Requestable Completeable";

                onTriggered:
                {
                    topBar.clearAll();
                    task.taskTypeEnum = 1;
                    task.visible = true;
                    hideMenuBar();
                }
            }
            MenuItem
            {
                text: "Requestable Repeatable";
                onTriggered:
                {
                    topBar.clearAll();
                    task.taskTypeEnum = 2;
                    task.visible = true;
                    hideMenuBar();
                }
            }
            MenuItem
            {
                text: "Settime Completeable";
                onTriggered:
                {
                    topBar.clearAll();
                    task.taskTypeEnum = 3;
                    task.visible = true;
                    hideMenuBar();
                }
            }
        }

        Menu
        {
            title: "Manage Catagories"
            id: manageCatagoriesMenu
            MenuItem
            {
                text: "New Catagory";
                onTriggered:
                {
                    createCatDialog.visible = true; topBar.clearAll();
                }
            }
            MenuItem
            {
                text: "Browse Tasks";
                onTriggered:
                {
                    topBar.clearAll();
                    browseTasks.visible = true;
                }
            }
        }
    }

    BrowseTasks
    {
        id: browseTasks
        visible: false
    }

    onClosing:
    {
        TaskManager.preQuitCleanup();
    }

    BrowseTasksDialog
    {
        id: browseTaskDialog
    }

    CreateCatDialog
    {
        id: createCatDialog
    }

    AddGoalViewToPaneDialog
    {
        id: addGoalView
        visible: false
    }

    CreateTask_KC
    {
        id: task
        visible: false
        onCompleted:
        {
            clearData();
            visible = false;
            showMenuBar();
        }
    }

    Item
    {
        id: tester

        ListView
        {
            id: list

        }
    }
}
