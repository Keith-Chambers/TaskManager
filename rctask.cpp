#include "rctask.h"

rcTask::rcTask(QString name, QString desc, quint16 catId, quint16 taskId, quint8 motivation, quint8 priority, QObject *parent):
    Task(name, desc, catId, taskId, parent)
{
    this->motivation = motivation;
    this->priority = priority;
    qDebug() << "Successfully added Task";
}

rcTask::rcTask(QDataStream &in)
{
    deserialize(in);
}

rcTask::rcTask(Task *const base): Task(base)
{

}

void rcTask::display(void)
{
    displayGeneric();
    qDebug() << "Motivation: " << motivation;
    qDebug() << "Priority: " << priority;
}

void rcTask::serialize(QDataStream &out)
{
    Task::serialize(out);

    out << motivation;
    out << priority;
}

void rcTask::deserialize(QDataStream &in)
{
    Task::deserialize(in);

    in >> motivation;
    in >> priority;

    //display();
}

void rcTask::partSerialize(QDataStream &out)
{
    out << motivation;
    out << priority;
}

void rcTask::partDeserialize(QDataStream &in)
{
    in >> motivation;
    in >> priority;
}

rcTask::rcTask(rcTask &task):
    Task(task)
{
    motivation = task.getMotivation();
    priority = task.getPriority();
}

rcTask::rcTask(void):
    Task()
{
    motivation = 0;
    priority = 0;
}

quint8 rcTask::getMotivation(void)
{
    return motivation;
}

quint8 rcTask::getPriority(void)
{
    return priority;
}

void rcTask::setMotivation(quint8 motivation)
{
    this->motivation = motivation;
}

void rcTask::setPriority(quint8 priority)
{
    this->priority = priority;
}
