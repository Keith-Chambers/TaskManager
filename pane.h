#ifndef PANE_H
#define PANE_H

#include <QDate>
#include <QVector>
#include <QObject>
#include <QJSEngine>
#include <QQmlEngine>
#include <QDataStream>

#include "./goalview.h"

class Pane : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Pane)
    Q_PROPERTY(QDate endDate READ getEndDate WRITE setEndDate NOTIFY endDateChanged)
    Q_PROPERTY(QDate startDate READ getStartDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(qint16 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString idStr READ getIdStr WRITE setIdStr NOTIFY idStrChanged)

public:
    // Constructors
    Pane(QDate endDate, QDate startDate, quint8 id);
    Pane(QDate endDate, QDate startDate);
    Pane(QDataStream &in);
    Pane();

    // Getters
    QDate getEndDate(void){ return endDate; }
    QDate getStartDate(void){ return startDate; }
    qint16 getId();
    quint8 getGoalViewCount() { return goalViews.size(); }
    const QVector<GoalView*> getGoalViewVec(void){ return goalViews; }
    QString getIdStr();

    // Setters
    void setEndDate(QDate date){ endDate = date; }
    void setStartDate(QDate date){ startDate = date; }
    void setIdStr(QString id){ qDebug() << "Error, this function should not be used"; Q_UNUSED(id) }

    // General
    Q_INVOKABLE bool addGoalView(GoalView *goalView);

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);

    // Unused
    void setId(qint16 id){ qDebug() << "Setting ID is not allowed"; Q_UNUSED(id); }

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new Pane;
    }

signals:
    void endDateChanged();
    void startDateChanged();
    void idChanged();
    void idStrChanged();

private:
    // Constants
    static const quint8 MAXPANESIZE = 5;
    // Member Variables
    QDate endDate;
    QDate startDate;
    qint16 id;
    QVector<GoalView*> goalViews;

};

#endif // PANE_H
