#include "task.h"

Task::Task(QString name, QString desc, quint16 catId, qint16 id, QObject *parent)
{
    Q_UNUSED(parent);
    this->name = name;
    this->desc = desc;
    deleted = false;
    taskId = id;
    archieved = false;
    // Assign taskId from metaData.nextTaskId
    this->catId = catId;

}

void Task::serialize(QDataStream &out)
{
    out << name;
    out << desc;
    out << deleted;
    out << archieved;
    out << taskId;
    out << catId;
    out << (quint16) timeMethod;
    out << (quint16) taskType;
}

void Task::deserialize(QDataStream &in)
{
    in >> name;
    in >> desc;
    in >> deleted;
    in >> archieved;
    in >> taskId;
    in >> catId;

    quint16 tempTimeMethod;
    quint16 tempTaskType;

    in >> tempTimeMethod;
    in >> tempTaskType;

    timeMethod = (TimeMethod) tempTimeMethod;
    taskType = (TaskType) tempTaskType;
}

void Task::displayGeneric()
{
    qDebug() << "Name: " << name;
    qDebug() << "Desc: " << desc;
    qDebug() << "Deleted: " << deleted;
    qDebug() << "Archieved: " << archieved;
    qDebug() << "Task Id: " << taskId;
    qDebug() << "Cat Id: " << catId;
    qDebug() << "Time Method: " << timeMethod;
    qDebug() << "Task Type: " << taskType;
}

Task::Task(Task &task):
    QObject()
{
    name = task.getName();
    desc = task.getDesc();
    deleted = task.isDeleted();
    archieved = task.isArchieved();
    taskId = task.getTaskId();
    catId = task.getCatId();
    timeMethod = task.getTimeMethod();
    taskType = (TaskType) task.getTaskType();
}

Task::Task(Task *const task):
    QObject()
{
    name = task->getName();
    desc = task->getDesc();
    deleted = task->isDeleted();
    archieved = task->isArchieved();
    taskId = task->getTaskId();
    catId = task->getCatId();
    timeMethod = task->getTimeMethod();
    taskType = (TaskType) task->getTaskType();
}

Task::Task(void)
{
    name = "Default Name";
    desc = "Default Desc";
    deleted = true;
    archieved = true;
    catId = 0;
    taskId = 0;
    timeMethod = NONE;
    taskType = SR;
}

void Task::setCatId(quint16 id)
{
    catId = id;
}

void Task::setTimeMethod(TimeMethod time)
{
    timeMethod = time;
}

bool Task::isDeleted(void)
{
    return deleted;
}

bool Task::isArchieved(void)
{
    return archieved;
}

QString Task::getName(void)
{
    return name;
}

void Task::setTaskId(qint16 id)
{
    qDebug() << "WARNING: Program is try to change ID of a task";
    taskId = id;
}

void Task::setTaskType(qint16 type)
{
    qDebug() << "WARNING: Program is trying to set task type of a task";
    taskType = TaskType (type);
}

TimeMethod Task::getTimeMethod(void)
{
    return timeMethod;
}

TaskType Task::getTaskType(void)
{
    return taskType;
}

void Task::setDeleted(bool val)
{
    deleted = val;
}

void Task::setArchieved(bool val)
{
    archieved = val;
}

void Task::setName(QString name)
{
    this->name = name;
}

void Task::setDesc(QString desc)
{
    this->desc = desc;
}

QString Task::getDesc(void)
{
    return desc;
}

quint16 Task::getCatId(void)
{
    return catId;
}

quint16 Task::getTaskId(void)
{
    return taskId;
}

bool Task::nameMatches(QString str)
{
    if(name == str)
    {
        return true;
    }else
    {
        return false;
    }
}





