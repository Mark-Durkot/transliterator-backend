#ifndef TRANSLITERATORFACTORY_H
#define TRANSLITERATORFACTORY_H

#include <QString>

#include "../transliterator/Transliterators/Transliterator.h"
#include "../transliterator/Transliterators/PinyinUkrainianTransliterator.h"
#include "../transliterator/Transliterators/GermanUkrainianTransliterator.h"
#include "../transliterator/Transliterators/SpanishUkrainianTransliterator.h"
#include "../transliterator/Transliterators/PassportUkrainianTransliterator.h"
#include "../transliterator/Transliterators/ScientificUkrainianTransliterator.h"
#include "../transliterator/LanguageStructures/LanguagePair.h"

class TransliteratorFactory
{
public:
    TransliteratorFactory();

    static Transliterator *createTransliterator(const QString &sourceLanguage, const QString &targetLanguage);
};

#endif // TRANSLITERATORFACTORY_H
