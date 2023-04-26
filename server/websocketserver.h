#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QWebSocket>
#include <QWebSocketServer>
#include <QThreadPool>
#include <QUrlQuery>

#include "transliterationchat.h"
#include "logger/logger.h"

#include "../transliterator/Transliterators/Transliterator.h"
#include "transliteratorfactory.h"

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    WebSocketServer(Logger *logger, QObject *parent=nullptr);

    void startServer();

private slots:
    void incomingConnection();
    void closeConnection();

private:
    QWebSocketServer *server;
    Logger *logger;
};

#endif // WEBSOCKETSERVER_H
