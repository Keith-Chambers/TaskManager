#include "taskcontainer.h"

void TaskContainer::setTasks(QVector<Task*> taskVec)
{
    qDebug() << "Manually setting task data";
    tasks = taskVec;
    qDebug() << "Setting nextTaskId to " << tasks.last()->getTaskId();
    nextTaskId = tasks.last()->getTaskId() + 1;
}

TaskContainer::TaskContainer(QQmlApplicationEngine *engine)
{
    qDebug() << "Empty constructer for taskContainer";
    this->engine = engine;
    loadGoalViewsToContext();
    nextTaskId = 1;
}

QVector<rcTask*> TaskContainer::getRcTasks(void)
{
    qDebug() << "Getting rcTasks";
    QVector<rcTask*> rcVec;
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->getTaskType() == RC)
        {
            rcVec.append((rcTask*) tasks.at(i));
            qDebug() << "Appending " << tasks.at(i)->getName();
        }
    }

    qDebug() << "Complete";
    return rcVec;
}

bool TaskContainer::loadGoalViewsToContext()
{
    qDebug() << "Loading all GoalViews to context";
    qObGoalViews.clear();

    for(int i = 0; i < rrTasks.size(); i++)
    {
        if(rrTasks.at(i)->isArchieved())
        { continue; }

        for(int x = 0; x < rrTasks.at(i)->numGoalViews(); x++)
        {
            qObGoalViews.append((QObject *) rrTasks.at(i)->goalViewAt(x));
        }
    }

    for(int i = 0; i < srTasks.size(); i++)
    {
        if(srTasks.at(i)->isArchieved())
        { continue; }

        for(int x = 0; x < srTasks.at(i)->numGoalViews(); x++)
        {
            qObGoalViews.append((QObject *) srTasks.at(i)->goalViewAt(x));
        }
    }

    engine->rootContext()->setContextProperty("goalViewModel", QVariant::fromValue(qObGoalViews));
    qDebug() << "Complete";

    return true;
}

bool TaskContainer::loadGoalViewsToContext(quint16 taskId)
{
    qDebug() << "Loading GoalViews to context of Id" << taskId;
    qObGoalViews.clear();

    for(int i = 0; i < rrTasks.size(); i++)
    {
        if(rrTasks.at(i)->isArchieved() || rrTasks.at(i)->getTaskId() != taskId)
        { continue; }

        for(int x = 0; x < rrTasks.at(i)->numGoalViews(); x++)
        {
            qObGoalViews.append((QObject *) rrTasks.at(i)->goalViewAt(x));
        }
        engine->rootContext()->setContextProperty("goalViewModel", QVariant::fromValue(qObGoalViews));
        qDebug() << "Complete";
        return true;
    }

    for(int i = 0; i < srTasks.size(); i++)
    {
        if(srTasks.at(i)->isArchieved() || srTasks.at(i)->getTaskId() != taskId)
        { continue; }

        for(int x = 0; x < srTasks.at(i)->numGoalViews(); x++)
        {
            qObGoalViews.append((QObject *) srTasks.at(i)->goalViewAt(x));
        }

        engine->rootContext()->setContextProperty("goalViewModel", QVariant::fromValue(qObGoalViews));
        qDebug() << "Complete";
        return true;
    }

    qDebug() << "Failed to find task of Id" << taskId;
    return false;
}

void TaskContainer::clearGoalViewContext(void)
{
    qObGoalViews.clear();
    engine->rootContext()->setContextProperty("goalViewModel", QVariant::fromValue(qObGoalViews));
    qDebug() << "goalViewContext cleared";
}

void TaskContainer::clearTaskContext(void)
{
    qObTasks.clear();
    engine->rootContext()->setContextProperty("TaskModel", QVariant::fromValue(qObTasks));
    qDebug() << "Tasks cleared from context";
}

// Remove this later
QString TaskContainer::getName(quint16 taskId)
{
    return getTask(taskId)->getName();
}

void TaskContainer::loadTasksToContextIfGoalView(void)
{
    qDebug() << "Loading Tasks with goalViews to context";
    qObTasks.clear();

    for(int i = 0; i < rrTasks.size(); i++)
    {
        if(rrTasks.at(i)->isArchieved())
        { continue; }

        if(rrTasks.at(i)->numGoalViews() > 0)
        {
            qDebug() << "Appending " << rrTasks.at(i)->getName();
            qObTasks.append((QObject *) rrTasks.at(i));
        }
    }

    for(int i = 0; i < srTasks.size(); i++)
    {
        if(srTasks.at(i)->isArchieved())
        { continue; }

        if(srTasks.at(i)->numGoalViews() > 0)
        { qObTasks.append((QObject *) srTasks.at(i)); }
    }

    engine->rootContext()->setContextProperty("TaskModel", QVariant::fromValue(qObTasks));
    qDebug() << "Complete";
}

QVector<rrTask*> TaskContainer::getRrTasks(void)
{
    qDebug() << "Getting rrTasks";

    QVector<rrTask*> rrVec;
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->getTaskType() == RR)
        {
            rrVec.append((rrTask*) tasks.at(i));
            qDebug() << "Appending " << tasks.at(i)->getName();
        }
    }

    qDebug() << "Complete";

    return rrVec;
}

QVector<scTask*> TaskContainer::getScTasks(void)
{
    qDebug() << "Getting scTasks";

    QVector<scTask*> scVec;
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->getTaskType() == SC)
        {
            scVec.append((scTask*) tasks.at(i));
            qDebug() << "Appending " << tasks.at(i)->getName();
        }
    }
    qDebug() << "Complete";

    return scVec;
}

QVector<srTask*> TaskContainer::getSrTasks(void)
{
    qDebug() << "Getting srTasks";

    QVector<srTask*> srVec;
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->getTaskType() == SR)
        {
            srVec.append((srTask*) tasks.at(i));
            qDebug() << "Appending " << tasks.at(i)->getName();
        }
    }

    qDebug() << "Complete";
    return srVec;
}

Task* TaskContainer::getTask(quint16 taskId)
{
    qDebug() << "Fetching task by Id(" << taskId << ")";
    qint16 index;
    index = binarySearch(0, tasks.size() - 1, taskId, tasks);
    if(index == -1)
    { return NULL; }

    qDebug() << "Returning " << tasks.at(index)->getName();

    return tasks.at(index);
}

qint16 TaskContainer::binarySearch(quint16 start, quint16 end, quint16 needle, const QVector<Task*> &data)
{
    if(end >= data.size())
    {
        qDebug() << "End value is out of range";
        return -1;
    }

    qDebug() << "Binary Search call[Start, end, needle]" << start << end << needle;

    if(start > end)
    {
        qDebug() << "Failed to find task with ID" << needle;
        return -1;
    }

    quint16 middle;

    if(start == end)
    {
        middle = start;
    }else
    {
        // Calc middle
        if((end - start) == 1)
        {
            middle = end;
        }else
        {
            middle = (end - start) / 2 + start;
        }
    }

    qDebug() << "Middle: " << middle << "; Id: " << data.at(middle)->getTaskId();

    if(data.at(middle)->getTaskId() == needle)
    {
        qDebug() << "Returning " << data.at(middle)->getName();
        return middle;
    }else if(data.at(middle)->getTaskId() > needle)
    {
        return binarySearch(start, middle - 1, needle, data);
    }else
    {
        return binarySearch(middle + 1, end, needle, data);
    }
}

GoalView *TaskContainer::getGoalView(quint16 taskId, quint8 goalViewId)
{
    Task *temp = getTask(taskId);
    qDebug() << "Task Type of" << temp->getTaskType();
    switch(temp->getTaskType())
    {
    case RR:
    {
        rrTask *task = (rrTask *) temp;
        return task->getGoalView(goalViewId);
        break;
    }
    case SR:
    {
        srTask *task = (srTask *) temp;
        return task->getGoalView(goalViewId);
        break;
    }
    default:
        qDebug() << "Failed to find valid repeatable task";
        return NULL;
    }
}

bool TaskContainer::append(Task* task)
{
    qDebug() << "Appending " << task->getName();

    switch(task->getTaskType())
    {
        case RC:
        {
            rcTask* temp = (rcTask*) task;
            rcTasks.append(temp);
            break;
        }
        case RR:
        {
            rrTask* temp = (rrTask*) task;
            rrTasks.append(temp);
            break;
        }
        case SC:
        {
            scTask* temp = (scTask*) task;
            scTasks.append(temp);
            break;
        }
        case SR:
        {
            srTask* temp = (srTask*) task;
            srTasks.append(temp);
            break;
        }
        default:
            qDebug() << "Error, invalid taskType";
            return false;
        }

    tasks.append(task);
    qDebug() << "Successfully appended task";

    return true;
}

bool TaskContainer::saveTasksToFile(void)
{
    qDebug() << "Saving tasks to file";
    clearTaskFile();
    QFile file(settings.TASKFDIR.absolutePath());

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open Tasks.bin";
        return false;
    }

    QDataStream out(&file);

    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->isDeleted() == false)
        {
            switch(tasks.at(i)->getTaskType())
            {
            case RC:
            {
                rcTask *rc = (rcTask*) tasks.at(i);
                rc->serialize(out);
                qDebug() << "Serializing " << tasks.at(i)->getName() << " to rc";
                continue;
            }
            case RR:
            {
                rrTask *rr = (rrTask*) tasks.at(i);
                rr->serialize(out);
                qDebug() << "Serializing " << tasks.at(i)->getName() << " to rr";
                continue;
            }
            case SC:
            {
                scTask *sc = (scTask*) tasks.at(i);
                sc->serialize(out);
                qDebug() << "Serializing " << tasks.at(i)->getName() << " to sc";
                continue;
            }
            case SR:
            {
                srTask *sr = (srTask*) tasks.at(i);
                sr->serialize(out);
                qDebug() << "Serializing " << tasks.at(i)->getName() << " to sr";
                continue;
            }
            default:
                qDebug() << "Invalid taskType encountered when saving tasks. Quiting function("
                         << tasks.at(i)->getTaskType() << ")";
                return false;
            }
        }else
        {
            qDebug() << tasks.at(i)->getName() << " not appended(Deleted)";
        }
    }

    file.flush();
    file.close();

    qDebug() << "Successfully saved Task data";

    return true;
}

bool TaskContainer::loadTasksFromFile(void)
{
    qDebug() << "Loading task data from file";
    QFile file(settings.TASKFDIR.absolutePath());

    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open Tasks.bin";
        return false;
    }

    QDataStream in(&file);
    quint8 debugCounter = 0;

    while(file.atEnd() == false)
    {
        qDebug() << "New Task Found(#" << debugCounter + 1 << ")";
        Task temp;
        temp.deserialize(in);
        debugCounter++;

        switch((TaskType) temp.getTaskType())
        {
            case RC:
            {
                rcTask *rcTemp = new rcTask(&temp);
                rcTemp->partDeserialize(in);
                addRc(rcTemp);
                qDebug() << "Added " << rcTemp->getName() << " to rc";
                break;
            }
            case RR:
            {
                rrTask *rrTemp = new rrTask(&temp);
                rrTemp->partDeserialize(in);
                addRr(rrTemp);
                qDebug() << "Added " << rrTemp->getName() << " to rr";
                break;
            }
            case SC:
            {
                scTask *scTemp = new scTask(&temp);
                scTemp->partDeserialize(in);
                addSc(scTemp);
                qDebug() << "Added " << scTemp->getName() << " to sc";
                break;
            }
            case SR:
            {
                srTask *srTemp = new srTask(&temp);
                srTemp->deserialize(in);
                addSr(srTemp);
                qDebug() << "Added " << srTemp->getName() << " to sr";
                break;
            }
            default:
                qDebug() << "Invalid task type(" << temp.getTaskType() << ")";
                return false;
        }
    }

    file.flush();   // Needed?
    file.close();

    qDebug() << "Successfully loaded Task data";
    return true;
}

quint16 TaskContainer::count(QVector<Task*> tasks)
{
    quint16 result = 0;

    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->isDeleted() == false){ result++; }
    }
    qDebug() << "Vector count is " << result;

    return result;
}

bool TaskContainer::editTask(QString name, QString desc, quint16 taskId)
{
    qDebug() << "Editing task(Id: " << taskId << ")";
    qint16 index = binarySearch(0, tasks.size(), taskId, tasks);
    if(-1 == index) { return false; }
    tasks.at(index)->setName(name);
    tasks.at(index)->setDesc(desc);

    return true;
}

bool TaskContainer::deleteTask(quint16 taskId)
{
    qDebug() << "Deleting task(Id: " << taskId << ")";
    qint16 index = binarySearch(0, tasks.size(), taskId, tasks);
    if(index == -1) { return false; }
    tasks.at(index)->setDeleted(true);

    qDebug() << "Successfully deleted";
    return true;
}

bool TaskContainer::archieveTask(quint16 taskId)
{
    qDebug() << "Archieving task(Id: " << taskId << ")";
    qint16 index = binarySearch(0, tasks.size(), taskId, tasks);
    if(index == -1) { return false; }
    tasks.at(index)->setArchieved(true);

    qDebug() << "Successfully Archieved";
    return true;
}

Task* TaskContainer::at(qint16 index)
{
    return tasks.at(index);
}

quint16 TaskContainer::size()
{
    return tasks.size();
}

void TaskContainer::clear(void)
{
    qDebug() << "Clearing all program data";
    rcTasks.clear();
    rrTasks.clear();
    scTasks.clear();
    srTasks.clear();
    tasks.clear();
    qDebug() << "Purge complete";
}

bool TaskContainer::addRc(QString name, QString desc, quint16 catId, quint8 motivation, quint8 priority, QObject * parent)
{
    qDebug() << "Adding rcTask by parameters";
    rcTask *temp = new rcTask(name, desc, catId, getNextTaskId(), motivation, priority, parent);
    temp->setTaskType(RC);
    return addRc(temp);
}

bool TaskContainer::addRr(QString name, QString desc, quint16 catId, quint8 motivation, QObject * parent)
{
    qDebug() << "Adding rrTask by parameters";
    rrTask *temp = new rrTask(name, desc, catId, getNextTaskId(), motivation, parent);
    temp->setTaskType(RR);
    return addRr(temp);
}

bool TaskContainer::addSc(QString name, QString desc, quint16 catId, quint16 year, quint8 month, quint8 day,
                           quint8 hour, quint8 minute, quint8 second, QObject *parent)
{
    qDebug() << "Adding scTask by parameters";
    scTask *temp = new scTask(name, desc, catId, getNextTaskId(), year, month, day, hour, minute, second, parent);
    temp->setTaskType(SC);
    return addSc(temp);
}

bool TaskContainer::addSr(QString name, QString desc, quint16 catId, QObject *parent)
{
    qDebug() << "Adding srTask by parameters";
    srTask *temp = new srTask(name, desc, catId, getNextTaskId(), parent);
    temp->setTaskType(SR);
    return addSr(temp);
}

bool TaskContainer::addRc(rcTask *task)
{
    qDebug() << "Adding rcTask direct";
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->nameMatches(task->getName()))
        {
            qDebug() << task->getName() << " already exist";
            return false;
        }
    }

    rcTasks.append(task);
    tasks.append((Task*) task);

    return true;
}

bool TaskContainer::addRr(rrTask *task)
{
    qDebug() << "Adding rrTask direct";
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->nameMatches(task->getName()))
        {
            qDebug() << task->getName() << " already exist";
            return false;
        }
    }

    rrTasks.append(task);
    tasks.append((Task*) task);

    return true;
}

bool TaskContainer::addSc(scTask *task)
{
    qDebug() << "Adding scTask direct";
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->nameMatches(task->getName()))
        {
            qDebug() << task->getName() << " already exist";
            return false;
        }
    }
    scTasks.append(task);
    tasks.append((Task*) task);

    return true;
}

bool TaskContainer::addSr(srTask *task)
{
    qDebug() << "Adding srTask directly";
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->nameMatches(task->getName()))
        {
            qDebug() << task->getName() << " already exist";
            return false;
        }
    }
    srTasks.append(task);
    tasks.append((Task*) task);

    return true;
}

QVector<Task*> TaskContainer::getTasksByCatagory(quint16 catId)
{
    qDebug() << "Getting tasks by catagory(Id: " << catId << ")";
    QVector<Task*> result;

    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->getCatId() == catId && tasks.at(i)->isDeleted() == false)
        {
            result.append(tasks.at(i));
            qDebug() << "Appending " << tasks.at(i)->getName();
        }
    }

    qDebug() << "Complete";
    return result;
}

QList<QObject*> TaskContainer::toObj(bool loadArchieved)
{
    qObTasks.clear();
    qDebug() << "Loading tasks for context scope";

    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->isDeleted() == false)
        {
            if(loadArchieved == true || tasks.at(i)->isArchieved() == false)
            {
                qDebug() << "Appending " << tasks.at(i)->getName();
                qObTasks.append((QObject*) tasks.at(i));
            }
        }
    }

    qDebug() << "Complete";
    return qObTasks;
}

void TaskContainer::loadTasksToContext(bool loadArchieved)
{
    qObTasks.clear();
    qDebug() << "Loading tasks to context";

    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->isDeleted() == false)
        {
            if(loadArchieved == true || tasks.at(i)->isArchieved() == false)
            {
                qDebug() << "Appending " << tasks.at(i)->getName();
                qObTasks.append((QObject*) tasks.at(i));
            }
        }
    }

    engine->rootContext()->setContextProperty("TaskModel", QVariant::fromValue(qObTasks));
    qDebug() << "Tasks Successfully loaded";
}

void TaskContainer::loadTasksToContextByCatagory(quint16 catId, bool loadArchieved)
{
    qObTasks.clear();
    qDebug() << "Loading tasks to context by catagory";

    for(int i = 0; i < tasks.count(); i++)
    {
        if(tasks.at(i)->isDeleted() == false && tasks.at(i)->getCatId() == catId)
        {
            if(loadArchieved == true || tasks.at(i)->isArchieved() == false)
            { qObTasks.append((QObject*) tasks.at(i)); }
        }
    }
    qDebug() << "Successfully loaded: " << qObTasks.size() << " tasks to context";

    engine->rootContext()->setContextProperty("TaskModel", QVariant::fromValue(qObTasks));
}

QList<QObject*> TaskContainer::toObjByCatagory(quint16 catId, bool loadArchieved)
{
    qObTasks.clear();
    qDebug() << "Fetching tasks by catagory Id " << catId;

    for(int i = 0; i < tasks.count(); i++)
    {
        if(tasks.at(i)->isDeleted() == false && tasks.at(i)->getCatId() == catId)
        {
            if(loadArchieved == true || tasks.at(i)->isArchieved() == false)
            {
                qDebug() << "Appending " << tasks.at(i)->getName();
                qObTasks.append((QObject*) tasks.at(i));
            }
        }
    }

    qDebug() << "Compelete";

    return qObTasks;
}

quint16 TaskContainer::getNextTaskId(void)
{
    return nextTaskId++;
}

bool TaskContainer::isNameStored(QString name)
{
    for(int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i)->isDeleted() == false && tasks.at(i)->nameMatches(name) == true)
        {
            qDebug() << name << " already stored";
            return true;
        }
    }

    return false;
}

void TaskContainer::clearTaskFile(void)
{
    qDebug() << "Clearing task file";
    QFile taskFile(settings.TASKFDIR.absolutePath());
    if(!taskFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to clear " << settings.TASKFDIR.absolutePath();
    }
    taskFile.resize(0);
}

quint8 TaskContainer::nextGoalViewId(quint16 taskId)
{
    switch(getTask(taskId)->getTaskType())
    {
        case RR:
        {
            rrTask* task = (rrTask*) getTask(taskId);
            return task->getNextGoalId();
        }
        case SR:
        {
            srTask* task = (srTask*) getTask(taskId);
            return task->getNextGoalId();
        }
        default:
        {
            qDebug() << "Invalid TaskType";
            return 0;
        }
    }
}

bool TaskContainer::addGoalView(GoalView *goalView)
{
    qDebug() << "Adding goalView";
    quint16 taskId = goalView->getTaskId();
    if(taskId < 1)
    {
        qDebug() << "Task ID wasn't set for goalView";
        return false;
    }

    qDebug() << "Seatching rrTasks";
    for(int i = 0; i < rrTasks.size(); i++)
    {
        if(rrTasks.at(i)->getTaskId() == taskId)
        {
            qDebug() << "Task found at " << i;
            if(false == rrTasks.at(i)->addGoalView(goalView)){ return false; }
            loadGoalViewsToContext();
            return true;
        }
    }
    qDebug() << "Searching srTasks";
    for(int i = 0; i < srTasks.size(); i++)
    {
        if(srTasks.at(i)->getTaskId() == taskId)
        {
            qDebug() << "Task found at " << i;
            if(false == srTasks.at(i)->addGoalView(goalView)){ return false; }
            loadGoalViewsToContext();
            return true;
        }
    }

    qDebug() << "Failed to find applicable task with id of " << taskId;
    return false;
}

bool TaskContainer::addGoalView(GoalView temp)
{
    quint16 taskId = temp.getTaskId();
    GoalView *goalView = new GoalView(temp.getGoalProgress(), temp.getEndDate(), temp.getTaskId(), temp.getGoalId());

    if(taskId < 1)
    {
        qDebug() << "Task ID wasn't set for goalView";
        return false;
    }

    for(int i = 0; i < rrTasks.size(); i++)
    {
        if(rrTasks.at(i)->getTaskId() == taskId)
        {
            rrTasks.at(i)->addGoalView(goalView);
            loadGoalViewsToContext();
            return true;
        }
    }

    for(int i = 0; i < srTasks.size(); i++)
    {
        if(srTasks.at(i)->getTaskId() == taskId)
        {
            srTasks.at(i)->addGoalView(goalView);
            loadGoalViewsToContext();
            return true;
        }
    }

    qDebug() << "Failed to find applicable task with id of " << taskId;
    return false;
}

















