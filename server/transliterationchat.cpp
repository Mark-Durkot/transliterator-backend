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

void TransliterationChat::messageRecieved(QString message)
{
    message = preProcessMessage(message);

    auto words = transliterator->transliterate(message);

    QJsonArray responseBody;
    QJsonObject responseJson;

    for (const auto &word : words) {
        QJsonObject wordObject;
        wordObject.insert("word", QJsonValue(word.text));
        wordObject.insert("type", QJsonValue(word.getTypeString()));
        responseBody.append(QJsonValue(wordObject));
    }

    socket->sendTextMessage(QJsonDocument(responseBody).toJson());
    socket->flush();
}

void TransliterationChat::socketDisconnected()
{
    emit socketDisconnect(socket);
    socket->deleteLater();
    transliterator->deleteLater();
    exit(0);
}

QString TransliterationChat::preProcessMessage(QString message)
{
    if (message.startsWith("\"") && message.endsWith("\"")) {
        message.remove(0, 1);
        message.remove(message.length() - 1, 1);
    }
    return message;
}
