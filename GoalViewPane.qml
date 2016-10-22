import QtQuick 2.0
import kdc.pane 1.0

Rectangle {
    id: root

    property int maxGoalViews: 3

    border.width: 1
    border.color: "Black"
    height: 450
    width: 350

    Component.onCompleted:
    {
        PaneManager.loadToContext();
    }

    Item
    {
        id: createNewPane
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        height: 30

        Rectangle
        {
            id: paneTopTextRect
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            color: "lightgrey"
            border.width: 1
            border.color: "Black"
            width: paneTopText.width + 20

            Text
            {
                id: paneTopText
                text: "Pane Section"
                color: "Black"
                font.bold: true;
                anchors.centerIn: parent
            }
        }

        Rectangle
        {
            id: addNewPaneRect
            anchors
            {
                top: parent.top
                right: parent.right
                left: paneTopTextRect.right
                bottom: parent.bottom
                rightMargin: 5
                leftMargin: -5
            }
            color: "lightblue"
            border.width: 1
            border.color: "Black"

            Text
            {
                id: addNewPaneText
                text: "Add Pane"
                color: "Black"
                anchors.centerIn: parent
                font.bold: true
            }

            PanelCreationDialog
            {
                id: panelCreation
                visible: false
                onQuit:
                {
                    visible = false;
                    // clearData();
                }
            }

            MouseArea
            {
                id: addPaneMouse
                anchors.fill: parent
                onClicked:
                {
                    console.log("Clicked");
                    if(PaneManager.numPanes() >= root.maxGoalViews)
                    {
                        console.log("Max Pane limit reached");
                        return;
                    }
                    panelCreation.visible = true;
                }
            }
        }
    }

    GridView
    {
        id: paneGridView
        width: 350
        anchors.top: createNewPane.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        cellHeight: 130
        cellWidth: 350
        interactive: false

        model: PaneModel

        delegate: Item
        {
            id: delegate
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }

            function updateGoalViewModel()
            {
                console.log("Updating goalViewModel")
                goalViewModel = PaneManager.getGoalViewModel(index)
                goalViewGrid.model = goalViewModel

                console.log(goalViewModel)
            }

            height: 120

            Text
            {
                id: paneNumber
                anchors.top: parent.top
                text: model.modelData.idStr
                color: "Black"
            }

            Rectangle
            {
                id: paneOptions
                anchors
                {
                    top: parent.top
                    right: parent.right
                }
                height: 20
                width: 100
                color: "lightblue"


                Rectangle
                {
                    id: removeRect
                    anchors
                    {
                        top: parent.top
                        bottom: parent.bottom
                        topMargin: 2
                        bottomMargin: 2
                        left: parent.left
                        leftMargin: 2
                    }

                    width: 25

                    border.width: 1
                    border.color: "Black"
                    color: "navy"

                    MouseArea
                    {
                        id: removeMouse
                        anchors.fill: parent
                        onClicked:
                        {
                            console.log("Clicked Delete pane");
                            var paneId = model.modelData.id;
                            console.log("paneId " + paneId);
                            console.log(model.modelData.id);
                            if(paneId == 0)
                            {   return; }
                            else
                            {   PaneManager.removePane(model.modelData.id); }
                        }
                    }
                }

                Rectangle
                {
                    id: addGoalView
                    anchors
                    {
                        top: parent.top
                        bottom: parent.bottom
                        topMargin: 2
                        bottomMargin: 2
                        left: removeRect.right
                        leftMargin: 2
                    }
                    width: 25
                    color: "yellow"
                    border.width: 1
                    border.color: "Black"

                    AddGoalViewToPaneDialog
                    {
                        id: addGoalViewToPane
                        visible: false
                        onSelectionComplete:
                        {
                            delegate.updateGoalViewModel();
                        }
                    }

                    MouseArea
                    {
                        id: addGoalViewMouse
                        anchors.fill: parent
                        onClicked:
                        {
                            console.log("Clicked");
                            addGoalViewToPane.targetPaneId = model.modelData.id
                            console.log("Targeting Pane " + addGoalViewToPane.targetPaneId);
                            addGoalViewToPane.visible = true;

                        }
                    }
                }
            }

            Rectangle
            {
                property int goalViewNum: 2


                id: goalViewContainer
                anchors
                {
                    top: paneOptions.bottom
                    left: parent.left
                    right: parent.right
                }
                height: 100
                color: "lightgrey"

                GridView
                {
                    id: goalViewGrid
                    anchors
                    {
                        left: parent.left
                        right: parent.right
                        leftMargin: 5
                        rightMargin: 5
                        top: parent.top
                        topMargin: 5
                        bottom: parent.bottom
                        bottomMargin: 5
                    }

                    interactive: false
                    cellWidth: parent.width - 10
                    cellHeight: 25
                    property variant goalViewModel: PaneManager.getGoalViewModel(index)

                    model: goalViewModel

                    delegate: Item
                    {
                        id: goalViewItem
                        height: 20
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors
                        {
                            left: parent.left
                            right: parent.right
                        }

                        Text
                        {
                            // elide
                            id: taskName
                            text: Tasks.getName(model.modelData.taskId);
                            width: 70
                            color: "Black"
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: goalEndRect.verticalCenter
                        }

                        Rectangle
                        {
                            id: goalEndRect
                            // width = totalWidthAvailable / (goalEndDate / paneEndDate)
                            height: parent.height
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            anchors.left: taskName.right
                            anchors.leftMargin: 5
                            border.width: 1
                            border.color: "Black"

                            Rectangle
                            {
                                id: goalProgress
                                property int percentage: 50
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                width: parent.width * (percentage / 100)
                                color: "red"
                            }
                        }

                        Rectangle
                        {
                            id: removeGoalView
                            anchors
                            {
                                left: goalEndRect.right
                                right: parent.right
                                leftMargin: 5
                                //rightMargin: 5
                                top: parent.top
                                bottom: parent.bottom
                                topMargin: 2
                                bottomMargin: 2
                            }
                            color: "green"

                            MouseArea
                            {
                                id: removeGoalViewMouse
                                anchors.fill: parent
                                onClicked:
                                {
                                    console.log("Clicked");
                                    //goalViewContainer.goalViewNum--;
                                    //PaneManager.find()
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
