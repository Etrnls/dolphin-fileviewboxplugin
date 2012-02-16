#ifndef FILEVIEWBOXPLUGIN_H
#define FILEVIEWBOXPLUGIN_H

#include <kversioncontrolplugin2.h>

#include <QHash>

class FileViewBoxPlugin : public KVersionControlPlugin2
{
    Q_OBJECT
public:
    FileViewBoxPlugin(QObject* parent, const QList<QVariant>& args);
    virtual ~FileViewBoxPlugin();

    virtual QString fileName() const;
    virtual bool beginRetrieval(const QString& directory);
    virtual void endRetrieval();
    virtual ItemVersion itemVersion(const KFileItem& item) const;
    virtual QList<QAction*> actions(const KFileItemList& items) const;
private:
    static QString sendCommand(const QString &command);

    QHash<QString, ItemVersion> m_versionInfoHash;
};

#endif
