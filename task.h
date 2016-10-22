#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QDebug>
#include <QDataStream>

enum TimeMethod {NULLTIME, TIME, QUANTITY, NONE};
enum TaskType {NULLTASK, RC, RR, SC, SR};

class Task : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qint16 taskId READ getTaskId WRITE setTaskId NOTIFY taskIdChanged)
    Q_PROPERTY(qint16 taskType READ getTaskType WRITE setTaskType NOTIFY taskTypeChanged)

public:
    // Constructors
    Task(QString name, QString desc, quint16 catId, qint16 id, QObject *parent = 0);
    Task(Task &task);
    Task(Task * const task);
    Task(void);
    ~Task(void){}

    // General functions
    bool nameMatches(QString str);
    void displayGeneric();

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);

    // Setters
    void setName(QString name);
    void setDesc(QString desc);
    void setDeleted(bool val);
    void setArchieved(bool val);
    void setTaskId(qint16 id);
    void setTaskType(qint16 type);
    void setCatId(quint16 id);
    void setTimeMethod(TimeMethod time);

    // Getters
    TimeMethod getTimeMethod(void);
    TaskType getTaskType(void);
    quint16 getTaskId(void);
    quint16 getCatId(void);
    QString getDesc(void);
    QString getName(void);
    bool isDeleted(void);
    bool isArchieved(void);

private:
    // Member Variables
    QString name;
    QString desc;
    bool deleted;
    bool archieved;
    qint16 taskId;
    quint16 catId;
    TimeMethod timeMethod;
    TaskType taskType;
signals:
    void nameChanged();
    void taskIdChanged();
    void taskTypeChanged();
};

#endif // TASK_H
