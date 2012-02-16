#include "fileviewboxplugin.h"

#include <kdebug.h>
#include <kfileitem.h>
#include <QDir>
#include <QLocalSocket>
#include <KDE/KPluginFactory>
#include <KDE/KPluginLoader>

K_PLUGIN_FACTORY(FileViewBoxPluginFactory, registerPlugin<FileViewBoxPlugin>();)
K_EXPORT_PLUGIN(FileViewBoxPluginFactory("fileviewboxplugin"))

FileViewBoxPlugin::FileViewBoxPlugin(QObject* parent, const QList<QVariant>& args) :
    KVersionControlPlugin2(parent)
{
    Q_UNUSED(args);
}

FileViewBoxPlugin::~FileViewBoxPlugin()
{
}

QString FileViewBoxPlugin::fileName() const
{
    return QLatin1String(".dropbox");
}

bool FileViewBoxPlugin::beginRetrieval(const QString& directory)
{
    m_versionInfoHash.clear();

    const QDir dir(directory);
    const QStringList files = dir.entryList();

    for (int i = 0; i < files.size(); ++i)
    {
        if (files.at(i) == QLatin1String(".") || files.at(i) == QLatin1String(".."))
            continue;

        const QString fileName = dir.absoluteFilePath(files.at(i));
        const QString command = QLatin1String("icon_overlay_file_status\npath\t") + fileName;

        const QString reply = sendCommand(command);
        if (reply.isEmpty())
            continue;

        const QStringList replySplitted = reply.split(QLatin1Char('\t'));
        if (replySplitted.size() < 2)
            continue;
        if (replySplitted.at(0) != QLatin1String("status"))
            continue;

        const QString state = replySplitted.at(1);
        ItemVersion version = UnversionedVersion;
        if (state == QLatin1String("up to date"))
            version = NormalVersion;
        else if (state == QLatin1String("syncing"))
            version = UpdateRequiredVersion;
        else if (state == QLatin1String("unsyncable"))
            version = ConflictingVersion;
        
        m_versionInfoHash.insert(fileName, version);
    }

    return true;
}

void FileViewBoxPlugin::endRetrieval()
{
}

FileViewBoxPlugin::ItemVersion FileViewBoxPlugin::itemVersion(const KFileItem& item) const
{
    const QString url = item.localPath();
    if (m_versionInfoHash.contains(url))
        return m_versionInfoHash.value(url);
    else
        return UnversionedVersion;
}

QList<QAction*> FileViewBoxPlugin::actions(const KFileItemList& items) const
{
    Q_UNUSED(items);
    return QList<QAction*>();
}

QString FileViewBoxPlugin::sendCommand(const QString &command)
{
    QLocalSocket socket;
    socket.connectToServer(QDir::home().absoluteFilePath(QLatin1String(".dropbox/command_socket")));

    if (!socket.waitForConnected()) {
        return QString();
    }

    socket.write((command + QLatin1String("\ndone\n")).toUtf8());
    socket.flush();

    QString reply;
    while (socket.waitForReadyRead())
    {
        reply.append(socket.readAll());
        if (reply.startsWith(QLatin1String("notok\n")))
            return QString();
        if (reply.endsWith(QLatin1String("\ndone\n")))
            break;
    }

    if (!reply.startsWith(QLatin1String("ok\n")))
        return QString();
    reply.remove(0, 3);

    if (!reply.endsWith(QLatin1String("\ndone\n")))
        return QString();
    reply.chop(6);
    
    return reply;
}

