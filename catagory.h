#ifndef CATAGORY_H
#define CATAGORY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QDebug>

#include "goalview.h"

class Catagory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qint16 id READ getId WRITE setId NOTIFY idChanged)
public:
    // Constructors
    Catagory(QString name, QString desc, quint16 catId);
    Catagory(QDataStream &in);
    Catagory(void);

    // Getters
    bool isDeleted(void);
    bool isArchieved(void);
    QString getName();
    void setName(QString name);
    qint16 getId(void);

    // Setters
    void setId(qint16 id);

    // General
    bool nameMatches(QString str);
    void display(void);
    bool addGoalView(GoalView *goalView);

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);

signals:
    void nameChanged();
    void idChanged();

private:
    // Member variables
    QString name;
    QString desc;
    bool deleted;
    bool archieved;
    qint16 id;
    QVector<quint16> subTaskIds;
    QVector<GoalView*> goalViews;
};

#endif // CATAGORY_H
