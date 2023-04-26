#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "logger.h"

#include <QObject>
#include <QDateTime>
#include <QDebug>

class ConsoleLogger : public Logger
{
    Q_OBJECT
public:
    ConsoleLogger();

    void info(const QString &message) override
    {
        qInfo() << formatMessage("INFO", message);
    }

    void log(const QString &message) override
    {
        qInfo() << formatMessage("LOG", message);
    }

    void error(const QString &message) override
    {
        qDebug() << formatMessage("ERROR", message);
    }

    void warning(const QString &message) override
    {
        qWarning() << formatMessage("WARNING", message);
    }
};

#endif // CONSOLELOGGER_H
