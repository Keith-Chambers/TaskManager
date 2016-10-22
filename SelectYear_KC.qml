import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle
{
    id: rect
    color: "lightgrey"
    height: 140
    width: 160
    border.width: 2
    border.color: "Black"
    radius: 3

    function clearData()
    {
        yearSpinBoxId.value = yearSpinBoxId.minimumValue;
        monthSpinBoxId.value = monthSpinBoxId.minimumValue;
        daySpinBoxId.value = daySpinBoxId.minimumValue;
    }
    property int year: yearSpinBoxId.value;
    property int month: monthSpinBoxId.value;
    property int day: daySpinBoxId.value;

    Label
    {
        id: titleLabelId
        text: "Set Date"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 5
        font.bold: true
    }

    Item
    {
        anchors.top: titleLabelId.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: childrenRect.height
        width: childrenRect.width

        Label
        {
            id: yearLabelId
            text: "Year: "
            color: "Black"
            anchors
            {
                left: parent.left
                verticalCenter: yearSpinBoxId.verticalCenter
            }
        }

        SpinBox
        {
            id: yearSpinBoxId
            anchors
            {
                left: monthSpinBoxId.left
            }

            maximumValue:
            {
                var x = new Date();
                return x.getFullYear() + 5;
            }

            minimumValue:
            {
                var x = new Date();
                return x.getFullYear();
            }

            onValueChanged: year = value;

            value:
            {
                return yearSpinBoxId.minimumValue;
            }
        }

        Label
        {
            id: monthLabelId
            text: "Month: "
            color: "Black"
            anchors
            {
                left: parent.left
                verticalCenter: monthSpinBoxId.verticalCenter
            }
        }

        SpinBox
        {
            id: monthSpinBoxId
            anchors
            {
                left: monthLabelId.right
                leftMargin: 10
                top: yearSpinBoxId.bottom
                topMargin: 10
            }

            maximumValue:
            {
                return 12;
            }

            minimumValue:
            {
                var x = new Date();

                if(yearSpinBoxId.value == x.getFullYear())
                    return x.getMonth() + 1;
                else
                    return 1;
            }

            onValueChanged: month = value;

            value:
            {
                return monthSpinBoxId.minimumValue;
            }
        }

        Label
        {
            id: dayLabelId
            text: "Day: "
            color: "Black"
            anchors
            {
                left: parent.left
                verticalCenter: daySpinBoxId.verticalCenter
            }
        }

        SpinBox
        {
            id: daySpinBoxId
            anchors
            {
                left: monthSpinBoxId.left
                top: monthSpinBoxId.bottom
                topMargin: 10
            }

            maximumValue:
            {
                // Set to month set in other part of program
                var d =  new Date();
                var x = new Date(d.getFullYear(), monthSpinBoxId.value + 1, 0);
                return x.getDate();
            }

            minimumValue:
            {
                var date = new Date();
                if(monthSpinBoxId.value == date.getMonth() + 1)
                    return date.getDate() + 1;
                else
                    return 1
            }

            onValueChanged: day = value;

            value:
            {
                return minimumValue;
            }
        }
    }
}

