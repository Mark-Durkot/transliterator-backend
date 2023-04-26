cmake_minimum_required(VERSION 3.16)
project(TransliteratorBackend VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui HttpServer WebSockets Xml)

qt_standard_project_setup()

qt_add_executable(TransliteratorBackend
    main.cpp
    server/httpserver.cpp server/httpserver.h
    server/logger/consolelogger.cpp server/logger/consolelogger.h
    server/logger/logger.h
    server/transliterationchat.cpp server/transliterationchat.h
    server/transliteratorfactory.cpp server/transliteratorfactory.h
    server/websocketserver.cpp server/websocketserver.h
    transliterator/LanguageStructures/LanguagePair.h
    transliterator/LanguageStructures/LanguagePairList.h
    transliterator/LanguageStructures/SyllablePair.h
    transliterator/LanguageStructures/SyllablePairList.h
    transliterator/Parsers/Words.h
    transliterator/Parsers/XMLParser.h
    transliterator/PerformanceBoosters/LanguagePairIndex.h
    transliterator/SyllableTree/SyllableTree.h
    transliterator/Transliterators/GermanUkrainianTransliterator.h
    transliterator/Transliterators/PassportUkrainianTransliterator.h
    transliterator/Transliterators/PinyinUkrainianTransliterator.h
    transliterator/Transliterators/ScientificUkrainianTransliterator.h
    transliterator/Transliterators/SpanishUkrainianTransliterator.h
    transliterator/Transliterators/Transliterator.h
    transliterator/Transliterators/TransliteratorList.h
)
target_link_libraries(TransliteratorBackend PRIVATE
    Qt::Core
    Qt::Gui
    Qt::HttpServer
    Qt::WebSockets
    Qt::Xml
)


# Resources:
set(libraries_resource_files
    "german_ukrainian.xml"
    "pinyin_ukrainian.xml"
    "spanish_ukrainian.xml"
    "ukrainian_passport.xml"
    "ukrainian_scientific.xml"
)

qt_add_resources(TransliteratorBackend "libraries"
    PREFIX
        "/"
    FILES
        ${libraries_resource_files}
)

install(TARGETS TransliteratorBackend
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET TransliteratorBackend
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
