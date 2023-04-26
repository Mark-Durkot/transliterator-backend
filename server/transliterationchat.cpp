#include "transliterationchat.h"

TransliterationChat::TransliterationChat(QWebSocket *socket, Transliterator *transliterator, QObject *parent)
    : QThread(parent), socket(socket), transliterator(transliterator)
{

}

TransliterationChat::~TransliterationChat()
{

}

void TransliterationChat::run()
{
    if (!socket)
    {
        return;
    }

    connect(socket, &QWebSocket::disconnected, this, &TransliterationChat::socketDisconnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &TransliterationChat::messageRecieved);
    exec();
}

QWebSocket *TransliterationChat::getSocket() const
{
    return socket;
}

void TransliterationChat::messageRecieved(const QString &message)
{
    auto result = transliterator->transliterate(message);
    auto response = result.join(QChar(' '));
    QJsonObject responseJson;
    responseJson.insert("result", QJsonValue(response));
    socket->sendTextMessage(QJsonDocument(responseJson).toJson());
    socket->flush();
}

void TransliterationChat::socketDisconnected()
{
    emit socketDisconnect(socket);
    socket->deleteLater();
    transliterator->deleteLater();
    exit(0);
}
