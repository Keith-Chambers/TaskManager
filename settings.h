#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDir>

class Settings
{
public:
    Settings(): SAVEPATH("/home/kchambers/.TMFiles"), PANEFDIR(SAVEPATH.absolutePath() + "/panes.bin"),
                TASKFDIR(SAVEPATH.absolutePath() + "/tasks.bin"),
                CATAGORYFDIR(SAVEPATH.absolutePath() + "/catagories.bin"){}

    const QDir SAVEPATH;
    const QDir PANEFDIR;
    const QDir TASKFDIR;
    const QDir CATAGORYFDIR;
    const quint8 MAXNPANES = 3;
};

#endif // SETTINGS_H
