#ifndef GOALVIEW_H
#define GOALVIEW_H

#include <QTime>
#include <QDate>
#include <QDebug>
#include <QDataStream>
#include <QQmlEngine>
#include <QJSEngine>

class GoalView : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GoalView)
    Q_PROPERTY(qint16 daysLeft READ daysLeft NOTIFY daysLeftChanged)
    Q_PROPERTY(qint16 goalId READ getGoalId WRITE setGoalId NOTIFY goalIdChanged)
    Q_PROPERTY(qint16 taskId READ getTaskId WRITE setTaskId NOTIFY taskIdChanged)

public:
    // Constructors
    GoalView(quint16 goalProgress, QTime endTime, QDate endDate, qint16 taskId, qint16 goalId);
    GoalView(quint16 goalProgress, QDate endDate, qint16 taskId, qint16 goalId);
    GoalView();
    Q_INVOKABLE void initialize(quint16 goalProgress, qint16 taskId, QDate endDate);

    // General
    bool equals(GoalView* goalView);
    void display();

    // Getters
    qint16 getTaskId();
    QTime getEndTime();
    QDate getEndDate();
    quint16 getGoalProgress();
    QTime getStartTime();
    QDate getStartDate();
    quint16 getCurrentProgress();
    qint16 daysLeft(void);
    qint16 getGoalId(void){ qDebug() << "Returning goalId of" << goalId; return goalId; }

    // Setters
    void setEndTime(QTime time);
    void setEndDate(QDate date);
    void setGoalProgress(quint16 progress);
    void updateCurrentProgress(quint16 toAdd);
    void setStartTime(QTime time);
    void setStartDate(QDate date);
    void setTaskId(qint16 taskId);
    void setGoalId(qint16 id){ goalId = id; }

    // Serialization
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new GoalView;
    }
private:
    // End date
    QTime endTime;
    QDate endDate;

    // Target goal
    quint16 goalProgress; // Hours or Items

    // Start Date
    QTime startTime;
    QDate startDate;

    // Current Progress
    quint16 currentProgress;

    // Both might end up redundent
    qint16 taskId;
    qint16 goalId;

signals:
    void daysLeftChanged();
    void goalIdChanged();
    void taskIdChanged();
};

#endif // GOALVIEW_H
