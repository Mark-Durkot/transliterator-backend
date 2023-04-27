#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "logger.h"

#include <QFile>
#include <QTextStream>

class FileLogger : public Logger
{
public:
    FileLogger();

    void info(const QString &message) override
    {
        writeToFile(formatMessage("INFO", message));
    }

    void log(const QString &message) override
    {
        writeToFile(formatMessage("LOG", message));
    }

    void error(const QString &message) override
    {
        writeToFile(formatMessage("ERROR", message));
    }

    void warning(const QString &message) override
    {
        writeToFile(formatMessage("WARNING", message));
    }

    void writeToFile(const QString &message)
    {
        QFile file("log.txt");


        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream fileStream(&file);
            fileStream << message;
            file.close();
        }
    }
};

#endif // FILELOGGER_H
