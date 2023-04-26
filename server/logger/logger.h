#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>

class Logger : public QObject
{
public:
    virtual void log(const QString &message) = 0;
    virtual void info(const QString &message) = 0;
    virtual void warning(const QString &message) = 0;
    virtual void error(const QString &message) = 0;

    static QString formatMessage(const QString &code, const QString &message)
    {
        return QDateTime::currentDateTimeUtc().toString() + " --[" + code + "]-- : " + message;
    }
};

#endif // LOGGER_H
