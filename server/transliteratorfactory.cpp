#include "transliteratorfactory.h"

TransliteratorFactory::TransliteratorFactory()
{

}

Transliterator *TransliteratorFactory::createTransliterator(const QString &source, const QString &target)
{
    if (source == "pinyin" && target == "ukrainian")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/pinyin_ukrainian.xml");
        return new PinyinUkrainianTransliterator(languagePair);
    }
    if (source == "ukrainian" && target == "pinyin")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/pinyin_ukrainian.xml");
        languagePair->swap();
        return new PinyinUkrainianTransliterator(languagePair);
    }
    if (source == "german" && target == "ukrainian")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/german_ukrainian.xml");
        return new GermanUkrainianTransliterator(languagePair);
    }
    if (source == "spanish" && target == "ukrainian")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/spanish_ukrainian.xml");
        return new SpanishUkrainianTransliterator(languagePair);
    }
    if (source == "ukrainian" && target == "passport")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/ukrainian_passport.xml");
        return new PassportUkrainianTransliterator(languagePair);
    }
    if (source == "ukrainian" && target == "scientific")
    {
        auto languagePair = LanguagePair::createLanguagePair(":/ukrainian_scientific.xml");
        return new ScientificUkrainianTransliterator(languagePair);
    }

    return nullptr;
}
