#include "mainwindow.h"
#include "ttkconcurrent.h"

#include <QDir>
#include <QMap>
#include <QFileInfo>
#include <QEventLoop>
#include <functional>

void foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool recursion)
{
    for(const auto &now: directory.entryInfoList(QDir::Files))
    {
        each(now);
    }

    if(recursion)
    {
        for(const auto &now: directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot))
        {
            foreachFileFromDirectory(now.filePath(), each, recursion);
        }
    }
}


void  MainWindow::codeLines(const QString &path)
{
    int fileCount = 0, lineCount = 0;

    if(path.isEmpty())
    {
        return;
    }

    QSet<QString> availableSuffixs;
    availableSuffixs << "h" << "c" << "cc" << "cp" << "cpp" << "hpp" << "inc"
                     << "i" << "ii" << "m" << "qml" << "pro" << "pri" << "prf" << "prl";

    QMap<QString, int> categorys;

    QEventLoop eventLoop;
    TTKConcurrent(
    {
        foreachFileFromDirectory( { path }, [&](const QFileInfo &fin)
        {
            QString suffix = TTK_FILE_SUFFIX(fin);
            if(suffix.isEmpty())
            {
               suffix = "other";
            }
            categorys.insert(suffix, categorys[suffix] + 1);

            QFile file(fin.filePath());
            if(!file.open(QIODevice::ReadOnly))
            {
                return;
            }

            fileCount++;

            const auto &&fileAllData = file.readAll();
            if(fileAllData.isEmpty())
            {
                return;
            }

            if(availableSuffixs.contains(suffix))
            {
                lineCount += fileAllData.count('\n') + 1;
            }
            file.close();
        }, true);

        eventLoop.quit();
    });

    eventLoop.exec();

    TTK_INFO_STREAM("All File Count " << fileCount);
    TTK_INFO_STREAM("All Meet The Requirements Line Count " << lineCount);

    for(const QString &key : categorys.keys())
    {
        TTK_INFO_STREAM(QString(".%1 Type  All count %2").arg(key).arg(categorys[key]));
    }
}
