#ifndef PANEMANAGER_H
#define PANEMANAGER_H

#include <QList>
#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDate>
#include <QFile>
#include <QVariant>

#include "pane.h"
#include "settings.h"

class PaneManager : public QObject
{
    Q_OBJECT
public:
    // Constructors
    PaneManager(QQmlApplicationEngine *engine);
    ~PaneManager(void);

    // File Management
    bool loadFromFile();
    bool saveToFile();
    void clear();
    bool clearFile();

    // Getters
    Q_INVOKABLE Pane *find(quint8 id);
    Q_INVOKABLE QVariant getGoalViewModel(quint8 paneId);
    Q_INVOKABLE qint8 numPanes();

    // Context Loading
    Q_INVOKABLE void loadGoalViewsToContext(quint8 paneIndex);
    Q_INVOKABLE void loadToContext(void);


    // General
    bool addPane(Pane *pane);
    Q_INVOKABLE bool addPane(QDate endDate);
    Q_INVOKABLE bool removePane(quint8 paneId);
    void removeAll(void);

private:
    // Member Variables
    QVector<Pane*> panes;
    QList<QObject*> qObPanes;
    QList<QObject*> qObPaneGoalViews;

    // Constants
    const quint8 MAXPANESIZE = 3;

    // Misc
    QQmlApplicationEngine *engine;
    Settings settings;
};

#endif // PANEMANAGER_H
