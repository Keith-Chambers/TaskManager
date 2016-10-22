#include "date.h"

bool Date::setDate(qint16 year, qint8 month, qint8 day, qint8 hour, qint8 minute, qint8 second)
{
    QDate current = QDate::currentDate();
    QDate passed = QDate(year, month, day);

    if(passed.isValid() == false)
    {
        qDebug() << "Passed date is invalid";
        return false;
    }

    qDebug() << current.daysTo(passed);

    if(current.daysTo(passed) < 1)
    {
        qDebug() << "Passed date is invalid(Only future dates allowed)";
        return false;
    }

    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;

    return true;
}

Date::Date(void)
{
    qDebug() << "Empty Date contructor called";
}

// Setters
void Date::setSecond(qint8 s)
{
    second = s;
}

void Date::setMinute(qint8 m)
{
    minute = m;
}

void Date::setHour(qint8 h)
{
    hour = h;
}

void Date::setDay(qint8 d)
{
    day = d;
}

void Date::setMonth(qint8 m)
{
    month = m;
}

void Date::setYear(qint16 y)
{
    year = y;
}
