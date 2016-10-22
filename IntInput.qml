import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4

Item {
    property alias maxLen: textFieldId.maximumLength;

    TextField {
        id: textFieldId
        maximumLength: 4
        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: 40
                implicitHeight: 24
                border.color: "#333"
                border.width: 1
            }
        }
    }

}
