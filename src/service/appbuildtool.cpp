#include "appbuildtool.h"

AppBuildtool::AppBuildtool(int &argc, char **argv)
    : super(argc, argv)
{
}

AppBuildtool::~AppBuildtool()
{
}

void AppBuildtool::prepare()
{
    if(systemTray.icon == Q_NULLPTR) {
        systemTray.menu = new QMenu();

        //the "MainView" will connect to "systemTray.restoreAction"
        systemTray.restoreAction = new QAction(tr("&Show"), this);
        systemTray.menu->addAction(systemTray.restoreAction);

        systemTray.menu->addSeparator();

        systemTray.quitAction = new QAction(tr("&Quit"), this);
        connect(systemTray.quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
        systemTray.menu->addAction(systemTray.quitAction);

        systemTray.icon = new QSystemTrayIcon(this);
        systemTray.icon->setIcon(this->windowIcon());
        systemTray.icon->setContextMenu(systemTray.menu);
        connect(systemTray.icon, &QSystemTrayIcon::activated, this, &AppBuildtool::onSystemTray);
    }
}

void AppBuildtool::toast(const QString &msg, int miliSeconds)
{
    if(systemTray.icon) {
        systemTray.icon->showMessage(this->applicationName(), msg, QSystemTrayIcon::Information, miliSeconds);
    }
}

void AppBuildtool::onSystemTray(QSystemTrayIcon::ActivationReason r)
{
    if(r != QSystemTrayIcon::Context) {
        systemTray.restoreAction->trigger();
    }
}
