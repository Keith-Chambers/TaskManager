import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: rootId
    height: 140
    width: 150
    color: "lightGrey"
    border.width: 2
    border.color: "black"
    radius: 3

    function clearData()
    {
        hourSpinBoxId.value = hourSpinBoxId.minimumValue;
        minuteSpinBoxId.value = minuteSpinBoxId.minimumValue;
        secondSpinBoxId.value = secondSpinBoxId.minimumValue;
    }

    property int hour: hourSpinBoxId.value;
    property int minute: minuteSpinBoxId.value;
    property int second: secondSpinBoxId.value;

    Label
    {
        id: titleLabel
        text: "Set Time"
        font.bold: true
        color: "Black"
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Item
    {
        id: timeContainerId
        height: childrenRect.height
        width: childrenRect.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleLabel.bottom

        Label
        {
            id: hourLabelId
            text: "Hour"
            color: "Black"
            anchors.left: parent.left
            anchors.verticalCenter: hourSpinBoxId.verticalCenter
        }

        SpinBox
        {
            id: hourSpinBoxId
            anchors
            {
                left: minuteLabelId.right
                leftMargin: 20
                top: parent.top
                topMargin: 10
            }

            onValueChanged: hour = value;

            maximumValue:
            {
                return 23;
            }

            minimumValue:
            {
                return 0;
            }

            value:
            {
                return hourSpinBoxId.minimumValue;
            }
        }

        Label
        {
            id: minuteLabelId
            text: "Minute"
            color: "Black"
            anchors.left: parent.left
            anchors.verticalCenter: minuteSpinBoxId.verticalCenter
        }

        SpinBox
        {
            id: minuteSpinBoxId
            anchors
            {
                left: minuteLabelId.right
                leftMargin: 20
                top: hourSpinBoxId.bottom
                topMargin: 10
            }

            maximumValue:
            {
                return 59;
            }

            minimumValue:
            {
                return 0;
            }

            onValueChanged: minute = value;

            value:
            {
                return minuteSpinBoxId.minimumValue;
            }
        }

        Label
        {
            id: secondLabelId
            text: "Second"
            color: "Black"
            anchors.left: parent.left
            anchors.verticalCenter: secondSpinBoxId.verticalCenter
        }

        SpinBox
        {
            id: secondSpinBoxId
            anchors
            {
                left: minuteLabelId.right
                leftMargin: 20
                top: minuteSpinBoxId.bottom
                topMargin: 10
            }

            maximumValue:
            {
                return 59;
            }

            minimumValue:
            {
                return 0;
            }

            onValueChanged: second = value;

            value:
            {
                return secondSpinBoxId.minimumValue;
            }
        }
    }
}
