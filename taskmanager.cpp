#include "taskmanager.h"

TaskManager::TaskManager(QQmlApplicationEngine *engine) : tasks(engine), paneManager(engine)
{
    qDebug() << "Constructing TaskManager Object";
    this->engine = engine;

    tasks.loadTasksFromFile();
    paneManager.loadFromFile();
    engine->rootContext()->setContextProperty("Tasks", &tasks);
    engine->rootContext()->setContextProperty("PaneManager", &paneManager);
    // quint16 timeScheduleSize;
    loadCatagories();
    loadCatagoryToContext();
    tasks.loadTasksToContext(engine);
    tasks.loadGoalViewsToContext();
}

void TaskManager::clearData(void)
{
    qDebug() << "Clearing Program Data";
    paneManager.clear();
    tasks.clear();
    catagories.clear();

    clearPersistantData();
}

bool TaskManager::clearPersistantData(void)
{
    qDebug() << "Clearing persistant data";

    tasks.clearTaskFile();
    paneManager.clearFile();

    QFile catagoryFile(settings.CATAGORYFDIR.absolutePath());
    if(!catagoryFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to clear " << settings.CATAGORYFDIR;
        return false;
    }
    catagoryFile.resize(0);

    qDebug() << "Complete";
    return true;
}

void TaskManager::loadTaskContextByCatagory(quint16 catId)
{
    tasks.loadTasksToContextByCatagory(catId, false);
}

void TaskManager::loadTasksToContext(void)
{
    tasks.loadTasksToContext(false);
}

void TaskManager::loadCatagoryToContext(void)
{
    qObCatagories.clear();

    qDebug() << "Catagories.size() = " << catagories.size();

    for(int i = 0; i < catagories.size(); i++)
    {
        if(catagories.at(i)->isDeleted() == false && catagories.at(i)->isArchieved() == false)
        {
            qObCatagories.append(catagories.at(i));
        }else
        {
            qDebug() << catagories.at(i)->getName() << " is not valid for adding tasks to";
        }
    }

    qDebug() << "Loading catagories to context";
    engine->rootContext()->setContextProperty("CatagoriesModel", QVariant::fromValue(qObCatagories));
    qDebug() << "Catagories successfully loaded to context";
}

Catagory *TaskManager::findCat(quint16 catId)
{
    for(int i = 0; i < catagories.size(); i++)
    {
        if(catagories.at(i)->getId() == catId)
        {
            return catagories.at(i);
        }
    }

    qDebug() << "Failed to find catagory";

    return NULL;
}

bool TaskManager::saveCatagories(void)
{
    QFile file(settings.CATAGORYFDIR.absolutePath());

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open " << settings.CATAGORYFDIR;
        return false;
    }

    QDataStream out(&file);
    quint8 numCatagories = catagories.size();
    out << numCatagories;

    qDebug() << numCatagories << " Catagories to write to file";
    for(int i = 0; i < numCatagories; i++)
    {
        catagories.at(i)->serialize(out);
    }

    file.flush();

    qDebug() << "Catagory Serialization complete";
    qDebug() << "";

    return true;
}

bool TaskManager::loadCatagories(void)
{
    QFile file(settings.CATAGORYFDIR.absolutePath());

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open " << settings.CATAGORYFDIR.absolutePath();
        return false;
    }

    QDataStream in(&file);
    quint8 numCatagories;
    in >> numCatagories;

    qDebug() << "Expecting " << numCatagories << "catagories";
    for(int i = 0; i < numCatagories; i++)
    {
        Catagory *cat = new Catagory(in);
        catagories.append(cat);
    }

    qDebug() << "Catagory deserialization complete";

    return true;
}

void TaskManager::preQuitCleanup(void)
{
    clearPersistantData();
    saveCatagories();
    tasks.saveTasksToFile();
    qDebug() << "Attempting to run paneManager function..";
    paneManager.saveToFile();

    catagories.clear();
    qObCatagories.clear();
}

bool TaskManager::addCatagory(QString name, QString desc)
{
    for(int i = 0; i < catagories.size(); i++)
    {
        if(catagories.at(i)->nameMatches(name) == true)
        {
            qDebug() << name << " already exists";
            return false;
        }
    }
    qDebug() << "Catagory successfully added";


    Catagory *newCat = new Catagory(name, desc, getNextCatId());
    catagories.append(newCat);
    loadCatagoryToContext();    // Inefficient

    return true;
}

quint16 TaskManager::getNextCatId(void)
{
    for(int i = catagories.size() - 1; i >= 0; i++)
    {
        if(catagories.at(i)->isDeleted() == false)
        { return catagories.at(i)->getId() + 1; }
    }

    // Initial catId
    return 1;
}

quint16 TaskManager::getCatId(quint16 catDisplayIndex)
{
    int counter = 0;

    for(int i = 0; i < catagories.size(); i++)
    {
        if(catagories.at(i)->isDeleted() == false && catagories.at(i)->isArchieved() == false)
        {

            if(counter == catDisplayIndex)
            {
                return catagories.at(i)->getId();
            }

            ++counter;
        }else
        {
            qDebug() << catagories.at(i)->getName() << " is inValid for use";
        }
    }

    qDebug() << "Failed to get catagory ID";

    // This is terrible
    return 0;
}
