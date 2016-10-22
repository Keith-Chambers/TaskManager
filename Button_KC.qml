import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {



    Rectangle
    {
        id: createTaskRect
        height: 30
        width: 150
        color: "lightblue"
        border.width: 1
        border.color: "black"
        radius: 5

        Label
        {
            id: createTaskLabel
            text: "Create Task"
            color: "black"
            anchors.centerIn: parent
            font.pointSize: 12
        }

        MouseArea
        {
            id: createTaskMouseArea
            anchors.fill: parent
            onClicked:
            {
                //console.log("Clicked")
            }
            onPressedChanged:
            {
                if(pressed == true)
                {
                    parent.color = "blue"
                }else
                {
                    parent.color = "lightblue"
                }
            }
        }
    }

}
