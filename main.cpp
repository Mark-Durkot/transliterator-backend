#include <QCoreApplication>
#include <QHttpServer>

#include "server/websocketserver.h"
#include "server/httpserver.h"

#include "server/logger/consolelogger.h"

#include "transliterator/Transliterators/PinyinUkrainianTransliterator.h"
#include "transliterator/Transliterators/GermanUkrainianTransliterator.h"
#include "transliterator/Transliterators/SpanishUkrainianTransliterator.h"
#include "transliterator/Transliterators/PassportUkrainianTransliterator.h"
#include "transliterator/Transliterators/ScientificUkrainianTransliterator.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Logger *logger = new ConsoleLogger();

    WebSocketServer *webSocketserver = new WebSocketServer(logger);
    webSocketserver->startServer();

    HttpServer *httpServer = new HttpServer(logger);
    httpServer->startServer();

    return a.exec();
}
