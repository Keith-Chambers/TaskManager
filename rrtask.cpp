#include "rrtask.h"

rrTask::rrTask(QString name, QString desc, quint16 catId, quint16 taskId, quint8 motivation, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    this->motivation = motivation;
    qDebug() << "Successfully added Task";
}

rrTask::rrTask(Task* base): Task(base)
{
    // Nothing to see here
}

rrTask::rrTask(QDataStream &in)
{
    deserialize(in);
}

GoalView *rrTask::goalViewAt(quint8 index)
{
    if(goalViews.size() <= index)
    {
        qDebug() << "Invalid index given for rrTask::goalViewAt() (" << index << ")";
        return NULL;
    }

    return goalViews.at(index);
}

quint8 rrTask::numGoalViews(void)
{
    return goalViews.size();
}

GoalView *rrTask::getGoalView(quint8 goalViewId)
{
    for(int i = 0; i < goalViews.size(); i++)
    {
        if(goalViews.at(i)->getGoalId() == goalViewId)
        { return goalViews.at(i); }
    }

    qDebug() << "Failed to find goalView of Id " << goalViewId;
    return NULL;
}

quint8 rrTask::getNextGoalId(void)
{
    return goalViews.last()->getGoalId() + 1;
}

bool rrTask::addGoalView(GoalView * goalView)
{
    qDebug() << "Adding to goalView to rr";

    if(goalViews.size() > 0)
    {
        goalView->setGoalId(goalViews.last()->getGoalId() + 1);
    }else
    {
        goalView->setGoalId(1);
    }
    qDebug() << "GoalId set to " << goalView->getGoalId();
    /* Disable duplicate endDate check
    for(int i = 0; i < goalViews.size(); i++)
    {
        if(goalViews.at(i)->getEndDate() == goalView->getEndDate())
        {
            qDebug() << "GoalViews in a task cannot share the same endDate";
            return false;
        }
    }
    */

    qDebug() << "Appending completed goalView to goalViews vector";
    goalViews.append(goalView);
    return true;
}

void rrTask::serializeGoalViews(QDataStream &out)
{
    qDebug() << "Serializing goalViews";
    quint16 size = goalViews.size();
    out << size;

    for(int i = 0; i < goalViews.size(); i++)
    {
        goalViews.at(i)->serialize(out);
    }

    qDebug() << "Complete";
}

void rrTask::deserializeGoalViews(QDataStream &in)
{
    qDebug() << "Deserializing goalViews";
    quint16 size;
    in >> size;

    // Create space for new GoalViews in vector
    for(int i = 0; i < size; i++)
    {
        goalViews.append(new GoalView());
    }

    for(int i = 0; i < size; i++)
    {
        goalViews.at(i)->deserialize(in);
    }
    qDebug() << "Complete";
}

void rrTask::serialize(QDataStream &out)
{
    Task::serialize(out);

    out << motivation;
    serializeGoalViews(out);
}

void rrTask::partSerialize(QDataStream &out)
{
    out << motivation;
    serializeGoalViews(out);
}

void rrTask::partDeserialize(QDataStream &in)
{
    in >> motivation;
    deserializeGoalViews(in);
}


void rrTask::deserialize(QDataStream &in)
{
    Task::deserialize(in);

    in >> motivation;
    deserializeGoalViews(in);

    //display();
}

rrTask::rrTask(void):
    Task()
{
    motivation = 0;
}

quint8 rrTask::getMotivation(void)
{
    return motivation;
}

void rrTask::setMotivation(quint8 motivation)
{
    this->motivation = motivation;
}

void rrTask::display(void)
{
    displayGeneric();
    qDebug() << "Motivation: " << motivation;
}
