import QtQuick 2.0
import QtQuick.Controls 1.4

Row
{
    function clearData()
    {
        console.log("SC: Clearing Data")
        timeId.clearData();
        dateId.clearData();
    }

    function validateInput()
    {
        return true;
    }

    property alias hour: timeId.hour
    property alias minute: timeId.minute
    property alias second: timeId.second
    property alias year: dateId.year
    property alias month: dateId.month
    property alias day: dateId.day

    spacing: 20
    SelectTime_KC{ id: timeId }
    SelectYear_KC{ id: dateId }

}
