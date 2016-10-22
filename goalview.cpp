#include "goalview.h"

GoalView::GoalView(quint16 goalProgress, QTime endTime, QDate endDate, qint16 taskId, qint16 goalId)
{
    qDebug() << "Constructing GoalView";
    qDebug() << endDate.toString();
    qDebug() << endTime.toString();
    this->goalProgress = goalProgress;
    this->endTime = endTime;
    this->endDate = endDate;
    startDate = QDate::currentDate();
    startTime = QTime::currentTime();
    this->taskId = (qint16) taskId;
    this->goalId = (qint8) goalId;
    currentProgress = 0;
}

GoalView::GoalView()
{
    qDebug() << "Empty GoalView constructor";
}

void GoalView::initialize(quint16 goalProgress, qint16 taskId, QDate endDate)
{
    this->goalProgress = goalProgress;
    if(endDate.isValid() == false)
    {
        qDebug() << "Error, invalid endDate passed";
        //return;
    }
    this->endDate = endDate;
    this->taskId = taskId;
}

GoalView::GoalView(quint16 goalProgress, QDate endDate, qint16 taskId, qint16 goalId)
{
    this->goalProgress = goalProgress;
    this->endDate = endDate;
    startDate = QDate::currentDate();
    startTime.setHMS(0, 0, 0, 0);
    endTime.setHMS(0, 0, 0, 0);
    this->taskId = taskId;
    this->goalId = goalId;
    currentProgress = 0;
}

qint16 GoalView::daysLeft(void)
{
    QDate temp = QDate::currentDate();
    qDebug() << "Current: " << temp.toString();
    qDebug() << "Target: " << endDate.toString();
    qint16 result = endDate.toJulianDay() - temp.toJulianDay();
    qDebug() << "Days Left: " << result;

    return endDate.toJulianDay() - temp.toJulianDay();
}

bool GoalView::equals(GoalView* goalView)
{
    if(goalView->getGoalId() == goalId && goalView->getTaskId() == taskId)
    {
        return true;
    }
    return false;
}

qint16 GoalView::getTaskId()
{
    return taskId;
}

QTime GoalView::getEndTime()
{
    return endTime;
}

QDate GoalView::getEndDate()
{
    return endDate;
}

quint16 GoalView::getGoalProgress()
{
    return goalProgress;
}

QTime GoalView::getStartTime()
{
    return startTime;
}

QDate GoalView::getStartDate()
{
    return startDate;
}

quint16 GoalView::getCurrentProgress()
{
    return currentProgress;
}

// Setters
void GoalView::setEndTime(QTime time)
{
    endTime = time;
}

void GoalView::setEndDate(QDate date)
{
    endDate = date;
}

void GoalView::setGoalProgress(quint16 progress)
{
    goalProgress = progress;
}

void GoalView::updateCurrentProgress(quint16 toAdd)
{
    currentProgress += toAdd;
}

void GoalView::setStartTime(QTime time)
{
    startTime = time;
}

void GoalView::setStartDate(QDate date)
{
    startDate = date;
}

void GoalView::setTaskId(qint16 taskId)
{
    this->taskId = taskId;
}

void GoalView::serialize(QDataStream &out)
{
    out << endDate.year();
    out << endDate.month();
    out << endDate.day();

    out << endTime.hour();
    out << endTime.minute();
    out << endTime.second();

    out << startDate.year();
    out << startDate.month();
    out << startDate.day();

    out << startTime.hour();
    out << startTime.minute();
    out << startTime.second();

    out << goalProgress;
    out << currentProgress;
    out << taskId;
    out << goalId;
}

void GoalView::deserialize(QDataStream &in)
{
    qint16 eYear, eMonth, eDay, eHour, eMinute, eSecond, sYear, sMonth, sDay, sHour, sMinute, sSecond = 0;

    in >> eYear;
    in >> eMonth;
    in >> eDay;

    in >> eHour;
    in >> eMinute;
    in >> eSecond;

    in >> sYear;
    in >> sMonth;
    in >> sDay;

    in >> sHour;
    in >> sMinute;
    in >> sSecond;

    endDate.setDate(eYear, eMonth, eDay);
    endTime.setHMS(eHour, eMinute, eSecond);

    startDate.setDate(sYear, sMonth, sDay);
    startTime.setHMS(sHour, sMinute, sSecond);

    in >> goalProgress;
    in >> currentProgress;

    in >> taskId;
    in >> goalId;

    qDebug() << "Checking GoalView integrety\n";
    display();
}

void GoalView::display()
{
    qDebug() << "EndDate";
    qDebug() << "Year:" << endDate.year();
    qDebug() << "Month:" << endDate.month();
    qDebug() << "Day:" << endDate.day();
    qDebug() << "";

    qDebug() << "EndTime";
    qDebug() << "Hour:" << endTime.hour();
    qDebug() << "Minutes:" << endTime.minute();
    qDebug() << "Seconds:" << endTime.second();
    qDebug() << "";

    qDebug() << "StartDate";
    qDebug() << "Year:" << startDate.year();
    qDebug() << "Month:" << startDate.month();
    qDebug() << "Day:" << startDate.day();
    qDebug() << "";

    qDebug() << "StartTime";
    qDebug() << "Hour:" << startTime.hour();
    qDebug() << "Minutes:" << startTime.minute();
    qDebug() << "Seconds:" << startTime.second();
    qDebug() << "";

    qDebug() << "GoalProgress:" << goalProgress;
    qDebug() << "CurrentProgress:" << currentProgress;
    qDebug() << "";

    qDebug() << "GoalId:" << goalId;
    qDebug() << "TaskId:" << taskId;
    qDebug() << "";
}
