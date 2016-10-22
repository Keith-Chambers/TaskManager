#ifndef RRTASK_H
#define RRTASK_H

#include <QVector>
#include <QObject>
#include <QString>
#include <QDebug>

#include "./task.h"
#include "./goalview.h"

class rrTask : public Task
{
public:
    // Constructors
    rrTask(QString name, QString desc, quint16 catId, quint16 taskId, quint8 motivation, QObject *parent = 0);
    rrTask(QDataStream &in);
    rrTask(Task* base);
    rrTask(void);
    ~rrTask(){}

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);
    void partSerialize(QDataStream &out);
    void partDeserialize(QDataStream &in);
    void deserializeGoalViews(QDataStream &in);
    void serializeGoalViews(QDataStream &out);

    // General
    void display();
    bool addGoalView(GoalView * goalView);
    quint8 numGoalViews(void);
    quint8 getNextGoalId(void);

    // Getters
    quint8 getMotivation(void);
    GoalView *getGoalView(quint8 goalViewId);
    GoalView *goalViewAt(quint8 index);

    // Setterss
    void setMotivation(quint8 motivation);

private:
    // Member Variables
    quint8 motivation;
    QVector<GoalView*> goalViews;
};

#endif // RRTASK_H
