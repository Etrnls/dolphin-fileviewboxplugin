#include "fileviewboxplugin.h"

#include <KPluginFactory>
#include <KPluginLoader>

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

