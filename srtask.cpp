#include "srtask.h"

srTask::srTask(QString name, QString desc, quint16 catId, quint16 taskId, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    qDebug() << "Successfully added Task";
    return;
}

srTask::srTask(QDataStream &in)
{
    deserialize(in);
}

srTask::srTask(void):
    Task()
{
    return;
}

GoalView *srTask::goalViewAt(quint8 index)
{
    if(goalViews.size() <= index)
    {
        qDebug() << "Invalid index given for srTask::goalViewAt() (" << index << ")";
        return NULL;
    }

    return goalViews.at(index);
}

quint8 srTask::numGoalViews(void)
{
    return goalViews.size();
}

GoalView *srTask::getGoalView(quint8 goalViewId)
{
    for(int i = 0; i < goalViews.size(); i++)
    {
        if(goalViews.at(i)->getGoalId() == goalViewId)
        { return goalViews.at(i); }
    }

    qDebug() << "Failed to find goalView of Id " << goalViewId;
    return NULL;
}

quint8 srTask::getNextGoalId(void)
{
    return goalViews.last()->getGoalId() + 1;
}

bool srTask::addGoalView(GoalView * goalView)
{
    if(goalViews.size() > 0)
    {
        goalView->setGoalId(goalViews.last()->getGoalId() + 1);
    }else
    {
        goalView->setGoalId(1);
    }
    /*
    for(int i = 0; i < goalViews.size(); i++)
    {
        if(goalViews.at(i)->getEndDate() == goalView->getEndDate())
        {
            qDebug() << "GoalViews in a task cannot share the same endDate";
            return false;
        }
    }
    */
    goalViews.append(goalView);
    return true;
}

void srTask::display(void)
{
    displayGeneric();
}

void srTask::serialize(QDataStream &out)
{
    Task::serialize(out);
    serializeGoalViews(out);
}

void srTask::serializeGoalViews(QDataStream &out)
{
    for(int i = 0; i < goalViews.size(); i++)
    {
        goalViews.at(i)->serialize(out);
    }
}

void srTask::deserializeGoalViews(QDataStream &in)
{
    for(int i = 0; i < goalViews.size(); i++)
    {
        goalViews.at(i)->deserialize(in);
    }
}

void srTask::deserialize(QDataStream &in)
{
    Task::serialize(in);
    deserializeGoalViews(in);
    display();
}

void partSerialize(QDataStream &out)
{
    Q_UNUSED(out);
    // SerializeGoalViews()
}

void partDeserialize(QDataStream &in)
{
    Q_UNUSED(in);
    // SerializeGoalViews()
}
