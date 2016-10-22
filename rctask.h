#ifndef RCTASK_H
#define RCTASK_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "./task.h"
#include <QDataStream>

class rcTask : public Task
{
public:
    // Constructors
    rcTask(QString name, QString desc, quint16 catId, quint16 taskId, quint8 motivation, quint8 priority, QObject *parent = 0);
    rcTask(QDataStream &in);
    rcTask(Task* const base);
    rcTask(rcTask &task);
    rcTask(void);
    ~rcTask(){}

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);
    void partSerialize(QDataStream &out);
    void partDeserialize(QDataStream &in);

    // Getters
    quint8 getMotivation(void);
    quint8 getPriority(void);

    // Setters
    void setMotivation(quint8 motivation);
    void setPriority(quint8 priority);

    // General
    void display();

private:
    // Member Variables
    quint8 motivation;
    quint8 priority;
};

#endif // RCTASK_H
