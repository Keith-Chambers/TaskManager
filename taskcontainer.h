#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include "./task.h"
#include "./rctask.h"
#include "./rrtask.h"
#include "./sctask.h"
#include "./srtask.h"
#include "settings.h"

#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class TaskContainer : public QObject
{

    Q_OBJECT
public:
    // Contructors
    TaskContainer(QQmlApplicationEngine *engine);

    // Getters
    QVector<rcTask*> getRcTasks(void);
    QVector<rrTask*> getRrTasks(void);
    QVector<scTask*> getScTasks(void);
    QVector<srTask*> getSrTasks(void);
    QList<QObject*> toObj(bool loadArchieved = false);                              // Deprecated
    QList<QObject*> toObjByCatagory(quint16 catId, bool loadArchieved = false);     // Deprecated
    QVector<Task*> getTasksByCatagory(quint16 catId);
    Q_INVOKABLE Task* getTask(quint16 taskId);
    Q_INVOKABLE GoalView *getGoalView(quint16 taskId, quint8 goalViewId);
    Q_INVOKABLE QString getName(quint16 taskId);

    // Container methods
    Task* at(qint16 index);
    quint16 size();
    bool append(Task* task);
    bool isNameStored(QString name);
    void clear(void);

    // Appending Data
    Q_INVOKABLE bool addRc(QString name, QString desc, quint16 catId, quint8 motivation, quint8 priority, QObject *parent = 0);
    Q_INVOKABLE bool addRr(QString name, QString desc, quint16 catId, quint8 motivation, QObject *parent = 0);
    Q_INVOKABLE bool addSc(QString name, QString desc, quint16 catId, quint16 year, quint8 month, quint8 day,
                               quint8 hour, quint8 minute, quint8 second, QObject *parent = 0);
    Q_INVOKABLE bool addSr(QString name, QString desc, quint16 catId, QObject *parent = 0);
    bool addRc(rcTask *task);
    bool addRr(rrTask *task);
    bool addSc(scTask *task);
    bool addSr(srTask *task);
    Q_INVOKABLE bool addGoalView(GoalView *goalView);
    bool addGoalView(GoalView temp);

    // General
    quint16 getNextTaskId(void);
    bool editTask(QString name, QString desc, quint16 taskId);
    Q_INVOKABLE bool deleteTask(quint16 taskId);
    Q_INVOKABLE bool archieveTask(quint16 taskId);
    quint8 nextGoalViewId(quint16 taskId);

    // File Management
    void clearTaskFile(void);
    bool loadTasksFromFile(void);
    bool saveTasksToFile(void);

    // Context Loading
    Q_INVOKABLE bool loadGoalViewsToContext();
    Q_INVOKABLE void clearGoalViewContext(void);
    Q_INVOKABLE void clearTaskContext(void);
    Q_INVOKABLE void loadTasksToContextByCatagory(quint16 catId, bool loadArchieved = false);
    Q_INVOKABLE void loadTasksToContext(bool loadArchieved = false);
    Q_INVOKABLE void loadTasksToContextIfGoalView(void);
    Q_INVOKABLE bool loadGoalViewsToContext(quint16 taskId);

    // Setters
    void setTasks(QVector<Task*> taskVec);

private:
    // Data vectors
    QVector<Task*> tasks;
    QVector<rcTask*> rcTasks;
    QVector<rrTask*> rrTasks;
    QVector<scTask*> scTasks;
    QVector<srTask*> srTasks;
    QList<QObject*> qObTasks;
    QList<QObject*> qObGoalViews;

    // Functions
    qint16 binarySearch(quint16 start, quint16 end, quint16 needle, const QVector<Task*> &data);
    quint16 count(QVector<Task*> tasks);

    // Variables
    QQmlApplicationEngine *engine;
    quint16 nextTaskId;
    Settings settings;
};

#endif // TASKCONTAINER_H
