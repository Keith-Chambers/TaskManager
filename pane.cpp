#include "pane.h"

Pane::Pane()
{
    qDebug() << "Empty constructor for Pane";
}

Pane::Pane(QDate endDate, QDate startDate, quint8 id)
{
    qDebug() << "Main contructor for Pane";
    this->endDate = endDate;
    this->startDate = startDate;
    this->id = id;
}

QString Pane::getIdStr()
{
    QString result;
    result = QString::number(id);
    qDebug() << id << "->" << result;
    return result;
}

void Pane::serialize(QDataStream &out)
{
    qDebug() << "Serializing Pane";
    out << id;

    out << (quint16) endDate.year();
    out << (quint16) endDate.month();
    out << (quint16) endDate.day();

    out << (quint16) startDate.year();
    out << (quint16) startDate.month();
    out << (quint16) startDate.day();

    quint16 size = goalViews.size();
    out << size;

    for(int i = 0; i < size; i++)
    {
        goalViews.at(i)->serialize(out);
    }
}

Pane::Pane(QDataStream &in)
{
    qDebug() << "Constructing Pane via deserialization";
    deserialize(in);
    qDebug() << "Complete";
}

void Pane::deserialize(QDataStream &in)
{
    in >> this->id;

    quint16 sYear, sMonth, sDay, eYear, eMonth, eDay;
    in >> eYear;
    in >> eMonth;
    in >> eDay;

    in >> sYear;
    in >> sMonth;
    in >> sDay;

    endDate.setDate(eYear, eMonth, eDay);
    startDate.setDate(sYear, sMonth, sDay);

    quint16 size;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        goalViews.append(new GoalView());
        goalViews.at(i)->deserialize(in);
    }

    qDebug() << "Pane Deserialized";
}

Pane::Pane(QDate endDate, QDate startDate)
{
    qDebug() << "Main contructor for Pane";
    this->endDate = endDate;
    this->startDate = startDate;
}

bool Pane::addGoalView(GoalView *goalView)
{
    if(goalViews.size() >= MAXPANESIZE)
    {
        qDebug() << goalViews.size() << "currently stored";
        qDebug() << MAXPANESIZE << "max";
        qDebug() << "Pane is at max size";
        for(int i = 0; i < goalViews.size(); i++)
        {
            qDebug() << "Goal Id" << goalViews.at(i)->getGoalId();
        }

        return false;
    }

    if(goalView->getEndDate() > this->endDate)
    {
        qDebug() << "Cannot add GoalView, time range is larger than pane supports";
        return false;
    }

    for(int i = 0; i < goalViews.size(); i++)
    {
        if(goalView->equals(goalViews.at(i)) == true)
        {
            qDebug() << "GoalView already exists in Pane";
            return false;
        }
    }

    goalViews.append(goalView);
    qDebug() << "GoalView successfully added to Pane";
    return true;
}

qint16 Pane::getId()
{
    qDebug() << "Return paneId of" << id;
    return id;
}
