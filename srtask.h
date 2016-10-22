#ifndef SRTASK_H
#define SRTASK_H

#include <QVector>
#include <QString>
#include <QTime>
#include <QDate>
#include <QObject>
#include <QDebug>
#include <QDataStream>

#include "./task.h"
#include "./goalview.h"

struct invokationSchedule
{
    QDate lastInvoked;
    quint8 dayInterval;
    QTime invokationTime;
};

class srTask : public Task
{
public:
    // Constructors
    srTask(QString name, QString desc, quint16 catId, quint16 taskId, QObject *parent = 0);
    srTask(QDataStream &in);
    srTask(Task * base): Task(base){}
    srTask(void);
    ~srTask(){}

    // General
    bool addGoalView(GoalView * goalView);
    void display();
    quint8 numGoalViews(void);
    quint8 getNextGoalId(void);

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);

    // Getters
    GoalView *getGoalView(quint8 goalViewId);
    GoalView *goalViewAt(quint8 index);

private:
    // Member variables
    QVector<GoalView*> goalViews;
    // Private Functions
    void serializeGoalViews(QDataStream &out);
    void deserializeGoalViews(QDataStream &in);

    // QVector<struct invokationSchedule> invokationTimes;
    // QDate terminationDate; // Set to archieve
    // QDate startDate;

};

#endif // SRTASK_H
