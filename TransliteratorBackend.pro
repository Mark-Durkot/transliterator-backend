QT -= gui
QT += websockets httpserver xml gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        server/httpserver.cpp \
        server/logger/consolelogger.cpp \
        server/logger/filelogger.cpp \
        server/transliterationchat.cpp \
        server/transliteratorfactory.cpp \
        server/websocketserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server/datasource/apidatasource.h \
    server/datasource/datasource.h \
    server/datasources/datasource.h \
    server/datasources/postgresdatasource.h \
    server/httpserver.h \
    server/logger/filelogger.h \
    server/logger/logger.h \
    server/logger/consolelogger.h \
    server/transliterationchat.h \
    server/transliteratorfactory.h \
    server/websocketserver.h \
    transliterator/LanguageStructures/LanguagePair.h \
    transliterator/LanguageStructures/LanguagePairList.h \
    transliterator/LanguageStructures/SyllablePair.h \
    transliterator/LanguageStructures/SyllablePairList.h \
    transliterator/Parsers/Words.h \
    transliterator/Parsers/XMLParser.h \
    transliterator/PerformanceBoosters/LanguagePairIndex.h \
    transliterator/SyllableTree/SyllableTree.h \
    transliterator/Transliterators/Transliterator.h \
    transliterator/Transliterators/TransliteratorList.h \
    transliterator/Transliterators/GermanUkrainianTransliterator.h \
    transliterator/Transliterators/PassportUkrainianTransliterator.h \
    transliterator/Transliterators/PinyinUkrainianTransliterator.h \
    transliterator/Transliterators/ScientificUkrainianTransliterator.h \
    transliterator/Transliterators/SpanishUkrainianTransliterator.h \

RESOURCES += \
    libraries.qrc

DISTFILES += \
    CMakeLists.txt \
    Dockerfile \
    Jenkinsfile \
    startup.sh
