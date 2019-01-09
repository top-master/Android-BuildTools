
#include "service/appbuildtool.h"

#include "component/mainview.h"

AppBuildtool *createApp(int &argc, char **argv) {
    AppBuildtool *app = new AppBuildtool(argc, argv);
    app->setWindowIcon(QIcon(QLL(":/images/icon.png")));
    app->prepare();

    MainView *w = new MainView();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

    app->systemTray.icon->setVisible(true);
    return app;
}

int main(int argc, char *argv[])
{
    QScopedPointer<AppBuildtool> app(
            createApp(argc, argv)
        );
    return app->exec();
}
