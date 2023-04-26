#ifndef TRANSLITERATIONCHAT_H
#define TRANSLITERATIONCHAT_H

#include <QThread>
#include <QWebSocket>

#include "../transliterator/Transliterators/Transliterator.h"

class TransliterationChat : public QThread
{
    Q_OBJECT
public:
    TransliterationChat(QWebSocket *socket, Transliterator *transliterator, QObject *parent=nullptr);
    ~TransliterationChat();

    void run() override;

    QWebSocket *getSocket() const;

signals:
    void socketDisconnect(QWebSocket *socket);

public slots:
    void messageRecieved(const QString &message);
    void socketDisconnected();

private:
    QWebSocket *socket;
    Transliterator *transliterator;
};

#endif // TRANSLITERATIONCHAT_H
