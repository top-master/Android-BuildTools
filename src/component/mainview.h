#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT
    typedef QWidget super;
public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

public slots:
    void build();

protected slots:
    void restore();

    void browseNdk();
    void browseQmake();
    void browseProject();

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
