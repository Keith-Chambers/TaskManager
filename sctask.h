#ifndef SCTASK_H
#define SCTASK_H

#include <QTime>
#include <QDate>
#include <QObject>
#include <QDebug>
#include "./task.h"

class scTask : public Task
{
public:
    // Constructors
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, quint8 minute, quint8 second, QObject *parent = 0);
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, quint8 minute, QObject *parent = 0);
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, quint8 hour, QObject *parent = 0);
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, quint8 day, QObject *parent = 0);
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, quint8 month, QObject *parent = 0);
    scTask(QString name, QString desc, quint16 catId, quint16 taskId, quint16 year, QObject *parent = 0);
    scTask(void);
    scTask(Task *base): Task(base) {}
    scTask(QDataStream &in);
    ~scTask(){}

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);
    void partSerialize(QDataStream &out);
    void partDeserialize(QDataStream &in);

    // General
    void display();

    // Getters
    QTime getTime(void);
    QDate getDate(void);

    // Setters
    void setTime(QTime time);
    void setDate(QDate date);

private:
    // Member Variables
    QTime time;
    QDate date;
};

#endif // SCTASK_H
