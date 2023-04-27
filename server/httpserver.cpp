#include "httpserver.h"

HttpServer::HttpServer(Logger *logger, QObject *parent)
    : QObject(parent), logger(logger)
{
    logger->setParent(this);

    server = new QHttpServer(this);

    server->route("/api/transliterate", QHttpServerRequest::Method::Get, [ ](const QHttpServerRequest &request)
    {
        QString sourceLanguage = request.query().queryItemValue("sourceLanguage");
        QString targetLanguage = request.query().queryItemValue("targetLanguage");

        if (sourceLanguage.isEmpty())
        {
            return QHttpServerResponse("Please specify a source language", QHttpServerResponse::StatusCode::BadRequest);
        }

        if (targetLanguage.isEmpty())
        {
            return QHttpServerResponse("Please specify a target language", QHttpServerResponse::StatusCode::BadRequest);
        }

        QJsonParseError error;

        QJsonObject jsonBody = QJsonDocument::fromJson(request.body(), &error).object();

        if (error.error != QJsonParseError::NoError)
        {
            return QHttpServerResponse("Invalid request body", QHttpServerResponse::StatusCode::BadRequest);
        }

        QString inputText = jsonBody.value("inputText").toString();

        Transliterator *transliterator = TransliteratorFactory::createTransliterator(sourceLanguage, targetLanguage);

        if (!transliterator)
        {
            return QHttpServerResponse("No transliterator found for language pair " + sourceLanguage + "-" + targetLanguage,
                                       QHttpServerResponse::StatusCode::InternalServerError);
        }

        auto words = transliterator->transliterate(inputText);

        QJsonArray responseBody;

        for (const auto &word : words) {
            QJsonObject wordObject;
            wordObject.insert("word", word.text);
            wordObject.insert("type", word.getTypeString());
            responseBody.append(wordObject);
        }

        return QHttpServerResponse(responseBody, QHttpServerResponse::StatusCode::Ok);
    });
}

void HttpServer::startServer()
{
    if (!server->listen(QHostAddress::Any, 8080))
    {
        logger->error("failed to start http server on port 8080");
    }
    else
    {
        logger->info("http server started on port 8080");
    }
}
