#include "catagory.h"

Catagory::Catagory(QString name, QString desc, quint16 catId)
{
    this->name = name;
    this->desc = desc;
    id = catId;
    deleted = false;
    archieved = false;
}

Catagory::Catagory(QDataStream &in)
{
    deserialize(in);
}

Catagory::Catagory(void)
{
    name = "Default";
    desc = "Default";
    id = 0;
    deleted = true;
    archieved = true;
}

void Catagory::display(void)
{
    qDebug() << "Name: " << name;
    qDebug() << "Desc: " << desc;
    qDebug() << "Id: " << id;
    qDebug() << "Deleted: " << deleted;
    qDebug() << "Archieved: " << archieved;
    qDebug() << ""; // New line
}

void Catagory::setId(qint16 id)
{
    this->id = id;
}

bool Catagory::addGoalView(GoalView *goalView)
{
    for(int i = 0; i < subTaskIds.size(); i++)
    {
        if(goalView->getTaskId() == subTaskIds.at(i))
        {
            break;
        }

        if(i == subTaskIds.size() - 1)
        {
            qDebug() << "GoalView refers to task not in target catagory";
            return false;
        }
    }

    qDebug() << "Successfully added goalView";
    goalViews.append(goalView);

    return true;
}

void Catagory::serialize(QDataStream &out)
{
    out << name;
    out << desc;
    out << deleted;
    out << archieved;
    out << id;
    out << subTaskIds;
}

void Catagory::deserialize(QDataStream &in)
{
    in >> name;
    in >> desc;
    in >> deleted;
    in >> archieved;
    in >> id;
    in >> subTaskIds;

    //display();
}

bool Catagory::nameMatches(QString str)
{
    if(name == str)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Catagory::isDeleted(void)
{
    return deleted;
}

bool Catagory::isArchieved(void)
{
    return archieved;
}

qint16 Catagory::getId(void)
{
    return id;
}

QString Catagory::getName()
{
    return name;
}

void Catagory::setName(QString name)
{
    this->name = name;
}
