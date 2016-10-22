#include "panemanager.h"

PaneManager::PaneManager(QQmlApplicationEngine *engine)
{
    qDebug() << "PaneManager constructor run";
    this->engine = engine;
    loadToContext();
}

PaneManager::~PaneManager(void)
{
    panes.clear();
    qObPanes.clear();
    qDebug() << "PaneManager destructed";
}

bool PaneManager::addPane(Pane *pane)
{
    qDebug() << "Adding pane";
    // Function needs to be able to check for duplicates
    quint8 id;
    if(panes.size() == 0)
    {
        id = 1;
    }else
    {
        id = panes.last()->getId() + 1;
    }

    Pane *temp = new Pane(pane->getStartDate(), pane->getEndDate(), id);
    panes.append(temp);
    loadToContext();
    qDebug() << "Successfully added new pane of id" << id;

    return true;
}

bool PaneManager::addPane(QDate endDate)
{
    qDebug() << "Adding pane";
    if(endDate.isValid() == false)
    {
        qDebug() << "Invalid end date passed";
        return false;
    }

    quint8 id;
    if(panes.size() == 0)
    {
        id = 1;
    }else
    {
        id = panes.last()->getId() + 1;
    }

    QDate start;
    start = QDate::currentDate();

    Pane *pane = new Pane(endDate, start, id);
    panes.append(pane);
    loadToContext();

    qDebug() << "Pane successfully added";
    return true;
}

bool PaneManager::removePane(quint8 paneId)
{
    qDebug() << "Removing task of Id " << paneId;

    for(int i = 0; i < panes.size(); i++)
    {
        if(panes.at(i)->getId() == paneId)
        {
            panes.removeAt(i);
            loadToContext();
            qDebug() << "Removed pane at index:" << i;
            return true;
        }
    }

    qDebug() << "Failed to find pane with an id of" << paneId;
    return false;
}

qint8 PaneManager::numPanes()
{
    return panes.size();
}

bool PaneManager::loadFromFile()
{
    qDebug() << "Loading pane data from file";
    QFile file(settings.PANEFDIR.absolutePath());

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open " << settings.PANEFDIR;
        return false;
    }

    QDataStream in(&file);
    quint16 size;
    in >> size;

    qDebug() << "Starting deserializing";
    for(int i = 0; i < size; i++)
    {
        panes.append(new Pane(in));
    }

    qDebug() << "Pane data successfully deserialized(" << size << " found)";
    file.flush();
    file.close();
    return true;
}

bool PaneManager::saveToFile()
{
    qDebug() << "Saving Pane data to file";
    QFile file(settings.PANEFDIR.absolutePath());
    qDebug() << "Pane data to be saved to " << settings.PANEFDIR.path();

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open " << settings.PANEFDIR.absolutePath();
        return false;
    }

    QDataStream out(&file);
    quint16 size = panes.size();
    out << size;
    qDebug() << size << " to write";

    for(int i = 0; i < panes.size(); i++)
    {
        panes.at(i)->serialize(out);
    }

    qDebug() << "Pane data successfully serialized";
    file.flush();
    file.close();
    return true;
}

void PaneManager::clear()
{
    qDebug() << "Pane data cleared";
    panes.clear();
    clearFile();
}

bool PaneManager::clearFile()
{
    QFile file(settings.PANEFDIR.absolutePath());
    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open " << settings.PANEFDIR.absolutePath();
        return false;
    }

    qDebug() << "Resizing file";
    file.resize(sizeof(quint16));
    QDataStream out(&file);
    quint16 size = 0;
    out << size;

    qDebug() << settings.PANEFDIR << " successfully cleared";
    file.flush();
    file.close();
    return true;
}

Pane *PaneManager::find(quint8 id)
{
    for(int i = 0; i < panes.size(); i++)
    {
        if(panes.at(i)->getId() == id)
        { return panes.at(i); }
    }

    qDebug() << "Failed to find requested pane (" << id << ")";
    return NULL;
}

void PaneManager::loadGoalViewsToContext(quint8 paneIndex)
{
    qDebug() << "Loading Panes, GoalViews to context";
    qObPaneGoalViews.clear();
    qDebug() << "Fetching goalView Data";
    const QVector<GoalView*> temp = panes.at(paneIndex)->getGoalViewVec();
    qDebug() << "Adding to context list";
    for(int i = 0; i < temp.size(); i++)
    {
        qObPaneGoalViews.append(temp.at(i));
    }

    qDebug() << "Adding goalView list to context";
    engine->rootContext()->setContextProperty("PaneGoalViewModel", QVariant::fromValue(qObPaneGoalViews));
    qDebug() << "Complete! GoalViews loaded from pane #" << paneIndex;
}

QVariant PaneManager::getGoalViewModel(quint8 paneIndex)
{
    qDebug() << "***Fetching goalView model for pane***";
    QList<GoalView*> result;
    const QVector<GoalView*> temp = panes.at(paneIndex)->getGoalViewVec();
    qDebug() << "Appending" << temp.size() << "models";

    for(int i = 0; i < temp.size(); i++)
    {
        result.append(temp.at(i));
        qDebug() << "Task Id:" << temp.at(i)->getTaskId() << "; GoalId:" << temp.at(i)->getGoalId();
    }

    return QVariant::fromValue(result);
}

void PaneManager::removeAll(void)
{
    qDebug() << "Clearing pane data";
    panes.clear();
}

void PaneManager::loadToContext(void)
{
    qDebug() << "Loading Panes to context";
    qObPanes.clear();

    for(int i = 0; i < panes.size(); i++)
    {
        // Should this be smarter?
        qDebug() << i + 1 << " currently being appended";
        qObPanes.append((QObject *) panes.at(i));
        qDebug() << "Appended";
    }
    qDebug() << "All panes appended";

    engine->rootContext()->setContextProperty("PaneModel", QVariant::fromValue(qObPanes));
    qDebug() << "Complete";
}
