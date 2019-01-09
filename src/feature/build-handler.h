#ifndef BUILDHANDLER_H
#define BUILDHANDLER_H

#include <QThread>
#include <QProcess>

class BuildHandler : protected QThread
{
    Q_OBJECT
    typedef QThread super;
public:
    BuildHandler();

    bool reset(const QString &ndkDir, const QString &qmakeFile, const QString &projectFile);

    inline void start(Priority p = InheritPriority) { super::start(p); }

    inline void addArch(const QString &cpuType) { m_archs += cpuType; }

    using QThread::finished;
Q_SIGNALS:
    void onArchitecture(const QString &type);

protected:
    // QThread interface
    void run() Q_DECL_OVERRIDE;

private:
    void warnInvalidPath(QLatin1Literal msg, const QString &path);

private:
    QString m_ndkDir;
    QString m_qmakeFile;
    QString m_projectFile;
    QStringList m_archs;
};

//class MakeTask {
//public:
//    inline MakeTask() {}
//    virtual ~MakeTask();
//    virtual void run();
//};

#endif // BUILDHANDLER_H
