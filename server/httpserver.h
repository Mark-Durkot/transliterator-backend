#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QHttpServer>

#include "logger/logger.h"
#include "transliteratorfactory.h"

class HttpServer : public QObject
{
    Q_OBJECT
public:
    HttpServer(Logger *logger, QObject *parent=nullptr);

    void startServer();

private:
    QHttpServer *server;
    Logger *logger;
};

#endif // HTTPSERVER_H
