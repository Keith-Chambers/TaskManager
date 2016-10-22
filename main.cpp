#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "./taskmanager.h"
#include "date.h"
#include "pane.h"
#include "goalview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    TaskManager taskMan(&engine);

    engine.rootContext()->setContextProperty("TaskManager", &taskMan);
    qmlRegisterSingletonType<Date>("kdc.date", 1, 0, "KDate", &Date::qmlInstance);
    qmlRegisterSingletonType<Pane>("kdc.pane", 1, 0, "KPane", &Pane::qmlInstance);
    qmlRegisterSingletonType<GoalView>("kdc.goalView", 1, 0, "GoalView", &GoalView::qmlInstance);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
