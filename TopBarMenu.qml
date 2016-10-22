import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

Item {
    // Make sure to set the height signals

    menuBar:
        MenuBar
        {
            Menu {
                title: "Create Task"
                MenuItem
                {
                    text: "Requestable + Repeatable"
                    onTriggered: console.log("Triggered")
                }
                MenuItem
                {
                    text: "Requestable + Completeable"
                    onTriggered: console.log("Triggered")
                }
                MenuItem
                {
                    text: "SetTime + Repeatable"
                    onTriggered: console.log("Triggered")
                }
                MenuItem
                {
                    text: "SetTime + Completeable"
                    onTriggered: console.log("Triggered")
                }
            }
            Menu
            {
                title: "Browse Tasks"
                MenuItem
                {
                    text: "Coding";
                    onTriggered: console.log("Browsing coding tasks");
                }
            }
        }
}
