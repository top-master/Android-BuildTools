#include "mainview.h"
#include "ui_mainview.h"

#include <service/appbuildtool.h>
#include <feature/build-handler.h>

#include <QFileDialog>


MainView::MainView(QWidget *parent)
    : super(parent)
    , ui(new Ui::MainView)
{
    ui->setupUi(this);

    QByteArray &path = qgetenv("ANDROID_NDK_ROOT");
    ui->ndkAddressEidit->setText(QString::fromLocal8Bit(path));

    connect(ui->ndkSelectButton, &QPushButton::clicked, this, &MainView::browseNdk);
    connect(ui->qmakeSelectButton, &QPushButton::clicked, this, &MainView::browseQmake);
    connect(ui->projectSelectButton, &QPushButton::clicked, this, &MainView::browseProject);
    connect(ui->buildButton, &QToolButton::clicked, this, &MainView::build);

    this->connect(qApp->systemTray.restoreAction, &QAction::triggered, this, &MainView::restore);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::build()
{
    QString &ndkDir = ui->ndkAddressEidit->text();
    QString &qmakeFile = ui->qmakeFileEdit->text();
    QString &projectFile = ui->projectFileEdit->text();

    BuildHandler maker;
    maker.reset(ndkDir, qmakeFile, projectFile);

    QCheckBox *archs[] = {
        ui->archArm
        , ui->archArm64
        , ui->archIntel
        , ui->archIntel64
        , ui->archMips
        , ui->archMips64
    };

    for (int i = 0; i < sizeof(archs) / sizeof(archs[0]); ++i) {
        if(archs[i]->isChecked()) {
            maker.addArch(archs[i]->text());
        }
    }

    maker.start();
}

void MainView::restore()
{
    this->showNormal();
    this->activateWindow();
}

void MainView::browseNdk()
{
    QString path = QFileDialog::getExistingDirectory(this
            , QLL("Select Android NDK"));
    if(!path.isEmpty())
        ui->ndkAddressEidit->setText(path);
}

void MainView::browseQmake()
{
    QString path = QFileDialog::getOpenFileName(this
            , QLL("Select qmake from XD framework"), QString()
            , QLL("XD qmake (qmake.exe)"));
    if(!path.isEmpty())
        ui->qmakeFileEdit->setText(path);
}

void MainView::browseProject()
{
    QString path = QFileDialog::getOpenFileName(this
            , QLL("Select Project"), QString()
            , QLL("Project File (*.pro)"));
    if(!path.isEmpty())
        ui->projectFileEdit->setText(path);
}
