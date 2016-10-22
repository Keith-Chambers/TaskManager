#include "sctask.h"

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, quint8 minute, quint8 second, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(hour, minute, second);
    date.setDate(year, month, day);
    qDebug() << "Successfully added Task";
}

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, quint8 minute, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(hour, minute, 0);
    date.setDate(year, month, day);
}

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(hour, 0, 0);
    date.setDate(year, month, day);
}

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(0, 0, 0);
    date.setDate(year, month, day);
}

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(0, 0, 0);
    date.setDate(year, month, 0);
}

scTask::scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, QObject *parent):
    Task(name, desc, catId, taskId)
{
    Q_UNUSED(parent);
    time.setHMS(0, 0, 0);
    date.setDate(year, 0, 0);
}

scTask::scTask(void):
    Task()
{
    time.setHMS(0, 0, 0);
    date.setDate(0, 0, 0);
}

scTask::scTask(QDataStream &in)
{
    deserialize(in);
}

QTime scTask::getTime(void)
{
    return time;
}

QDate scTask::getDate(void)
{
    return date;
}

void scTask::setTime(QTime time)
{
    this->time = time;
}

void scTask::setDate(QDate date)
{
    this->date = date;
}

void scTask::display(void)
{
    displayGeneric();

    qDebug() << "Year: " << date.year();
    qDebug() << "Month: " << date.month();
    qDebug() << "Day: " << date.day();

    qDebug() << "Hour: " << time.hour();
    qDebug() << "Minute: " << time.minute();
    qDebug() << "Second: " << time.second();
}

void scTask::serialize(QDataStream &out)
{
    Task::serialize(out);

    out << time;
    out << date;
}

void scTask::deserialize(QDataStream &in)
{
    in >> time;
    in >> date;

    display();
}

void scTask::partSerialize(QDataStream &out)
{
    out << time;
    out << date;
}

void scTask::partDeserialize(QDataStream &in)
{
    in >> time;
    in >> date;
}
































