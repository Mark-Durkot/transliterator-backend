#include "websocketserver.h"

WebSocketServer::WebSocketServer(Logger *logger, QObject *parent)
    : QObject(parent), logger(logger)
{
    logger->setParent(this);
    server = new QWebSocketServer("chat-server", QWebSocketServer::NonSecureMode, this);
    connect(server, &QWebSocketServer::newConnection, this, &WebSocketServer::incomingConnection);
}

void WebSocketServer::startServer()
{
    if (!server->listen(QHostAddress::Any, 1234))
    {
        logger->error("failed to start web socket server on port 1234");
        return;
    }
    else
    {
        logger->info("web socket server started on port 1234");
    }
}

void WebSocketServer::incomingConnection()
{
    auto socket = server->nextPendingConnection();

    if (!socket)
    {
        logger->error("failed to connect to socket");
        return;
    } else
    {
        logger->info("new connection: " + socket->requestUrl().toString() + ", peer: " + socket->peerAddress().toString());
    }

    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::closeConnection);

    auto url = socket->requestUrl();
    QUrlQuery query(url);
    auto transliteratorName = query.queryItemValue("transliterator");
    if (transliteratorName.size() == 0)
    {
        logger->error("missing path parameter: transliterator");
        socket->close();
        return;
    }

    auto language1 = transliteratorName.split("-")[0];
    auto language2 = transliteratorName.split("-")[1];


    Transliterator *transliterator = TransliteratorFactory::createTransliterator(language1, language2);

    if (!transliterator)
    {
        logger->error("failed to load transliterator: " + language1 + "-" + language2);
        return;
    }

    TransliterationChat *chat = new TransliterationChat(socket, transliterator, this);

    chat->start();
}

void WebSocketServer::closeConnection()
{
    auto socket = dynamic_cast<QWebSocket*>(sender());
    logger->info("closing connection: " + socket->requestUrl().toString() + ", peer: " + socket->peerAddress().toString() + ", error: " + socket->errorString());
}

