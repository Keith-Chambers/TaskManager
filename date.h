#ifndef DATE_H
#define DATE_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QQmlApplicationEngine>
#include <QJSEngine>
#include <QDebug>

class Date: public QObject
{

    Q_OBJECT
    Q_DISABLE_COPY(Date)
    Q_PROPERTY(qint8 second READ getSecond WRITE setSecond NOTIFY secondChanged)
    Q_PROPERTY(qint8 minute READ getMinute WRITE setMinute NOTIFY minuteChanged)
    Q_PROPERTY(qint8 hour READ getHour WRITE setHour NOTIFY hourChanged)
    Q_PROPERTY(qint8 day READ getDay WRITE setDay NOTIFY dayChanged)
    Q_PROPERTY(qint8 month READ getMonth WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(qint16 year READ getYear WRITE setYear NOTIFY yearChanged)

public:
    // Constants
    static const qint8 NULLVAL = -1;

    // Constructors
    Q_INVOKABLE Date(void);
    Q_INVOKABLE bool setDate(qint16 year = -1, qint8 month = -1, qint8 day = -1, qint8 hour = -1, qint8 minute = -1, qint8 second = -1);

    // Getters
    Q_INVOKABLE qint8 getSecond(){ return second; }
    Q_INVOKABLE qint8 getMinute(){ return minute; }
    Q_INVOKABLE qint8 getHour(){ return hour; }
    Q_INVOKABLE qint8 getDay(){ return day; }
    Q_INVOKABLE qint8 getMonth(){ return month; }
    Q_INVOKABLE qint16 getYear(){ return year; }

    // Setters
    void setSecond(qint8 s);
    void setMinute(qint8 m);
    void setHour(qint8 h);
    void setDay(qint8 d);
    void setMonth(qint8 m);
    void setYear(qint16 y);

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new Date;
    }

signals:
    void secondChanged();
    void minuteChanged();
    void hourChanged();
    void dayChanged();
    void monthChanged();
    void yearChanged();
private:
    // Functions

    // Variables
    qint8 second;
    qint8 minute;
    qint8 hour;
    qint8 day;
    qint8 month;
    qint16 year;
};

#endif // DATE_H
