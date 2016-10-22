#ifndef TaskManager_H
#define TaskManager_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QList>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QDataStream>
#include <QDate>
#include <QTime>

#include "./rctask.h"
#include "./rrtask.h"
#include "./sctask.h"
#include "./srtask.h"
#include "./catagory.h"
#include "./goalview.h"
#include "./pane.h"
#include "./taskcontainer.h"
#include "date.h"
#include "settings.h"
#include "panemanager.h"

class TaskManager : public QObject
{
    Q_OBJECT

public:
    // Constructors
    TaskManager(QQmlApplicationEngine *engine);

    // General
    Q_INVOKABLE quint16 getCatId(quint16 catDisplayIndex);
    Q_INVOKABLE bool addCatagory(QString name, QString desc);

    // Context Loading
    Q_INVOKABLE void loadTaskContextByCatagory(quint16 catId);

    // File Management
    bool clearPersistantData(void);
    Q_INVOKABLE void clearData(void);
    Q_INVOKABLE void preQuitCleanup(void);


private:

    // Private Functions
    quint16 getNextCatId(void);
    Catagory *findCat(quint16 catId);
    bool saveCatagories(void);
    bool loadCatagories(void);
    void loadCatagoryToContext(void);
    void loadTasksToContext(void);

    // Member Variables
    QQmlApplicationEngine *engine;
    QList<Catagory*> catagories;
    QList<QObject*> qObCatagories;
    TaskContainer tasks;
    Settings settings;
    PaneManager paneManager;

    // Constants
    static const quint8 MAXNUMPANES;

};

#endif // TaskManager_H
