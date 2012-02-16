#ifndef FILEVIEWBOXPLUGIN_H
#define FILEVIEWBOXPLUGIN_H

#include <kversioncontrolplugin2.h>

class FileViewBoxPlugin : public KVersionControlPlugin2
{
    Q_OBJECT
public:
    FileViewBoxPlugin(QObject* parent, const QList<QVariant>& args);
};

#endif
