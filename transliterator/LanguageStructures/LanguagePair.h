#ifndef LANGUAGEPAIR_H
#define LANGUAGEPAIR_H

#include "SyllablePairSet.h"
#include "../Parsers/XMLParser.h"

#include <QObject>

class LanguagePair : public QObject
{
    Q_OBJECT
public:
    LanguagePair(QObject *parent=nullptr)
        : QObject(parent)
    {
    }

    void operator=(const LanguagePair &l)
    {
        syllables  = l.syllables;
        exceptions = l.exceptions;

        sourceLanguageName     = l.sourceLanguageName;
        targetLanguageName    = l.targetLanguageName;
        twoWayTransliteration = l.twoWayTransliteration;

        currentSourceLanguageName = sourceLanguageName;
        currentTargetLanguageName = targetLanguageName;
    }

    static LanguagePair *createLanguagePair(const QString &filename)
    {
        XMLParser parser;
        parser.setContent(filename);

        LanguagePair *languagePair = new LanguagePair();

        languagePair->sourceLanguageName    = parser.parseFirstLanguageName();
        languagePair->targetLanguageName    = parser.parseSecondLanguageName();
        languagePair->twoWayTransliteration = parser.parseTwoWayTransliteration();

        languagePair->currentSourceLanguageName = languagePair->sourceLanguageName;
        languagePair->currentTargetLanguageName = languagePair->targetLanguageName;

        languagePair->syllables  = parser.parseSetByTagName("syllable");
        languagePair->exceptions = parser.parseSetByTagName("exception");

        return languagePair;
    }

    void swap()
    {
        if (twoWayTransliteration)
        {
            syllables.swap();
            exceptions.swap();
            qSwap(currentSourceLanguageName, currentTargetLanguageName);
            sortByDescendingSyllableLenght();
        }
    }

    void sortByDescendingSyllableLenght()
    {
        syllables.sortByDescendingSyllableLenght();
        exceptions.sortByDescendingSyllableLenght();
    }

    long getId() const { return id; }

    const SyllablePairSet &getSyllables()  const { return syllables;  }
    const SyllablePairSet &getExceptions() const { return exceptions; }

    const QString &getSourceLanguageName() const { return sourceLanguageName;    }
    const QString &getTargetLanguageName() const { return targetLanguageName;    }
    bool isTwoWayTransliteration() const         { return twoWayTransliteration; }

    const QString &getCurrentSourceLanguage() const { return currentSourceLanguageName; }
    const QString &getCurrentTargetLanguage() const { return currentTargetLanguageName; }

    QString getLanguagePairId() const
    {
        return sourceLanguageName.toLower() + "_" + targetLanguageName.toLower();
    }

    bool isPartOfException(QString s) const

    {
        s = s.toLower();

        for (const auto &e : exceptions)
        {
            for (auto word : e.getSource().split(" "))
            {
                while (word.endsWith("."))
                {
                    word.remove(word.length() - 1, 1);
                }

                if (word.toLower() == s) { return true; }
            }
        }

        return false;
    }

    bool isException(QString s) const
    {
        s = s.toLower();

        for (const auto &e : exceptions)
        {
            if (e.getSource().toLower() == s) { return true; }
        }

        return false;
    }

    void setSourceLanguage(QString s)
    {
        sourceLanguageName = s;
    }

    void setTargetLanguage(QString s)
    {
        targetLanguageName = s;
    }

    void setBidirectional(bool b)
    {
        twoWayTransliteration = b;
    }

    void setSyllables(SyllablePairSet s)
    {
        syllables = s;
    }

    void setExceptions(SyllablePairSet e)
    {
        exceptions = e;
    }

    void setId(long id)
    {
        this->id = id;
    }

private:
    long id;

    SyllablePairSet syllables;
    SyllablePairSet exceptions;

    QString sourceLanguageName;
    QString targetLanguageName;
    bool twoWayTransliteration;

    QString currentSourceLanguageName;
    QString currentTargetLanguageName;
};

#endif // LANGUAGEPAIR_H
