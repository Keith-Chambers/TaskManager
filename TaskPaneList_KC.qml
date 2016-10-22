import QtQuick 2.0

Item
{
    id: root
    height: listView.height

    Rectangle
    {
        height: 100;
        width: 100
        border.width: 1
        border.color: "black"

        Component
        {
            id: listDelegate;
            Rectangle
            {
                height: 40
                width: listView.width
                color: "lightblue"
                border.width: 1
                border.color: "black"
                Text
                {
                    text: "Name: " + model.modelData.name;
                    anchors.centerIn: parent
                }
            }

        }

        Component
        {
            id: listHeader

            Rectangle
            {
                id: rectId
                color: "yellow"
                height: 40
                width: listView.width
                border.width: 2
                border.color: "black"

                Text
                {
                    text: "Add Pane"
                    color: "black"
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked: console.log("CLicked!")
                }
            }
        }

        ListView
        {
            id: listView
            height: 100
            width: 100
            spacing: 1
            model: myModel
            clip: true
            header: listHeader
            delegate: listDelegate
        }
    }
}
