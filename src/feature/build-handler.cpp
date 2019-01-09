#include "build-handler.h"

#include <service/appbuildtool.h>

#include <QDir>

BuildHandler::BuildHandler()
{
}

bool BuildHandler::reset(const QString &ndkDir, const QString &qmakeFile, const QString &projectFile)
{
    QString &makerFile = QDir::cleanPath( ndkDir
            + QLL("/prebuilt/windows/bin/make.exe")
        );

    if(!QFileInfo(ndkDir).isDir()) {
        warnInvalidPath(QLL("NDK dir does not exist"), ndkDir);
        return false;
    }
    if(!QFile::exists(makerFile)) {
        warnInvalidPath(QLL("maybe NDK is invalid"), makerFile);
        return false;
    }
    if(!QFile::exists(qmakeFile)) {
        warnInvalidPath(QLL("qmake does not exist"), qmakeFile);
        return false;
    }
    if(!QFile::exists(projectFile)) {
        warnInvalidPath(QLL("project does not exist"), projectFile);
        return false;
    }

    m_ndkDir = ndkDir;
    m_qmakeFile = qmakeFile;
    m_projectFile = projectFile;
    m_archs.clear();

    return true;
}

void BuildHandler::run()
{
    foreach (const QString &architecture, m_archs) {
        QProcess qmake; {
            QStringList env = QProcess::systemEnvironment();
            env.append(QLL("ANDROID_NDK_ROOT=") + m_ndkDir);
            qmake.setEnvironment(env);
        }
        emit onArchitecture(architecture);
    }
}

void BuildHandler::warnInvalidPath(QLatin1Literal msg, const QString &path)
{
    QLL &suffix = QLL(", failed to find:\n");
    QString r;
    r.reserve(msg.size() + suffix.size() + path.size());
    r += msg;
    r += suffix;
    r += path;
    qApp->toast(r);
}


