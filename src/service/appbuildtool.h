#ifndef APPBUILDTOOL_H
#define APPBUILDTOOL_H

#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

#if defined(qApp)
#  undef qApp
#endif
#define qApp (static_cast<AppBuildtool *>(QCoreApplication::instance()))

class AppBuildtool : public QApplication
{
    Q_OBJECT
    typedef QApplication super;
public:
    AppBuildtool(int &argc, char **argv);
    ~AppBuildtool() Q_DEL_OVERRIDE;

    void prepare();

public slots:
    void toast(const QString &, int miliSeconds = 3000);

protected slots:
    void onSystemTray(QSystemTrayIcon::ActivationReason);

public:

    struct SystemTray {
        inline SystemTray()
            : restoreAction(0), quitAction(0)
            , menu(0), icon(0)
        {}
        inline ~SystemTray() {
            if(icon)
                icon->setVisible(false);
            delete menu;
        }

        QAction *restoreAction;
        QAction *quitAction;
        QMenu *menu;
        QSystemTrayIcon *icon;
    } systemTray;
};

#endif // APPBUILDTOOL_H
