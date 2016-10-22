import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.0 as Controls
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Item {
    id: root
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 50
    anchors.rightMargin: 50

    signal completed;
    property int taskTypeEnum: 0

    function validateInput()
    {
        // Make sure to validate catagory when viable
        if(nameInputId.text != "" && descInputId.text != "" && timeTypeId.currentIndex != 0)
        {
            switch(taskTypeEnum)
            {
            case 0:
                console.log("Error: Invalid taskTypeEnum");
                break;
            case 1:
                // RcTask
                return rcTask.validateInput();
            case 2:
                return rrTask.validateInput();
                // RrTask
            case 3:
                return scTask.validateInput();
                // ScTask
            case 4:
                // SrTask (Not in use)
                console.log("SrTask");
                return false;
            default:
                console.log("Error: Invalid taskTypeEnum(D)");
            }
        }
    }

    onVisibleChanged:
    {
        if(visible == true)
        {
            console.log(taskTypeEnum);
            switch(taskTypeEnum)
            {
            case 0:
                console.log("Error: Invalid Task Type Enum");
                break
            case 1:
                rcTask.visible = true;
                break;
            case 2:
                rrTask.visible = true;
                break;
            case 3:
                scTask.visible = true;
                break;
            }
        }else
        {
            clearData();
            taskTypeEnum = 0;
            rcTask.visible = false;
            rrTask.visible = false;
            scTask.visible = false;
        }
    }

    function clearData()
    {
        nameInputId.text = "";
        descInputId.text = "";
        timeTypeId.currentIndex = 0;
        catComboId.currentIndex = 0;

        if(rrTask.visible == true) { rrTask.clearData(); }
        if(rcTask.visible == true) { rcTask.clearData(); }
        if(scTask.visible == true) { scTask.clearData(); }

    }

    Label
    {
        id: nameLabelId
        text: "Name"
        color: "Black"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 20
    }


    TextField
    {
        id: nameInputId
        anchors.right: parent.right
        anchors.left: nameLabelId.right
        anchors.leftMargin: 10
        anchors.top: nameLabelId.top

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

    Label
    {
        id: descLabelId
        text: "Desc"
        color: "Black"
        anchors.left: nameLabelId.left
        anchors.top: descInputId.top
    }

    TextField
    {
        id: descInputId
        anchors.left: descLabelId.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.top:nameInputId.bottom
        anchors.topMargin: 10

        style: TextFieldStyle
        {
            background: Rectangle
            {
                radius: 2
                implicitHeight: 100
                implicitWidth: 300
                border.color: "#333"
                border.width: 1
            }
        }
    }

    ComboBox
    {
        id: timeTypeId
        width: 150
        model: ["Select Time Method", "Time Length", "Item Quantity", "None"]

        anchors.left: descInputId.left
        anchors.top: descInputId.bottom
        anchors.topMargin: 10

        style:
        ComboBoxStyle
        {
            textColor: "Black"
        }
    }

    ComboBox
    {
        id: catComboId
        anchors.left: timeTypeId.right
        anchors.leftMargin: 10
        anchors.top: timeTypeId.top
        width: 150
        model: CatagoriesModel
        textRole: "name"

        style: ComboBoxStyle
        {
            textColor: qsTr("Black")
        }
    }

    Button
    {
        text: "New Catagory"
        anchors.top: catComboId.top
        anchors.left: catComboId.right
        anchors.leftMargin: 10
        anchors.right: parent.right

        MouseArea
        {
            id: newCatMouse
            anchors.fill: parent
            onClicked: createCatDialog.visible = true
        }
    }

    CreateCatDialog
    {
        id: createCatDialog
    }

    Item
    {
        id: nonGenericTaskCreationContainer
        anchors.top: catComboId.bottom;
        anchors.topMargin: 20
        anchors.left: descInputId.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        RC_TaskCreation_KC
        {
            id: rcTask;
            visible: false
        }

        RR_TaskCreation_KC
        {
            id: rrTask;
            visible: false
        }

        SC_TaskCreation_KC
        {
            id: scTask;
            visible: false
        }
    }

    Item
    {
        id: controlButtons
        anchors
        {
            left: descInputId.left
            right: parent.right
            bottom: parent.bottom
        }

        Rectangle
        {
            id: nextButtonRect
            height: 25
            width: 120
            color: "lightblue"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            border.width: 1
            border.color: "Black"
            radius: 3

            Label
            {
                id: nextButtonLabel
                text: "Next"
                color: "black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: nextButtonMouse
                anchors.fill: parent
                onClicked:
                {
                console.log("Next Button Clicked");

                    if(validateInput() == true)
                    {
                        console.log("Data Validated..");
                        switch(taskTypeEnum)
                        {
                        case 1:
                            console.log("Adding RC");
                            Tasks.addRc(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex), rcTask.motivationValue, rcTask.priorityValue);
                            //TaskManager.addRcTask(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex), rcTask.motivationValue, rcTask.priorityValue);
                            break;
                        case 2:
                            console.log("Adding RR");
                            Tasks.addRr(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex), rrTask.motivationValue);
                            //TaskManager.addRrTask(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex), rrTask.motivationValue);
                            break;
                        case 3:
                            console.log("Adding SC");
                            TaskManager.addSc(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex),
                                                  scTask.year, scTask.month, scTask.day, scTask.hour, scTask.minute, scTask.second);
                            break;
                        case 4:
                            console.log("Adding SR");
                            TaskManager.addSr(nameInputId.text, descInputId.text, TaskManager.getCatId(catComboId.currentIndex));
                            break;
                        default:
                            console.log("Error: Invalid taskTypeEnum");
                            Qt.quit();
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id: cancelButtonRect
            height: 25
            width: 120
            color: "lightblue"
            anchors.bottom: nextButtonRect.bottom
            anchors.left: nextButtonRect.right
            anchors.leftMargin: 20
            border.width: 1
            border.color: "Black"
            radius: 3

            Label
            {
                id: cancelButtonLabel
                text: "Cancel"
                color: "black"
                anchors.centerIn: parent
            }

            MouseArea
            {
                id: cancelButtonMouse
                anchors.fill: parent
                onClicked: completed();
            }
        }
    }
}






















