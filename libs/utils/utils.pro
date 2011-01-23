# toolkit library project file
TEMPLATE = lib
TARGET = Utils
PACKAGE_VERSION = 0.4.0
DEFINES *= UTILS_LIBRARY

# include config file
include(../libsworkbench.pri)
include(../utils_dependencies.pri)

HEADERS += global_exporter.h \
    global.h \
    database.h \
    log.h \
    updatechecker_p.h \
    updatechecker.h \
    messagesender.h \
    serializer.h \
    licenseterms.h \
    randomizer.h \
    stylehelper.h \
    httpdownloader.h \
    iconbadgealert.h \
    qtcassert.h \
    widgets/scrollingwidget.h \
    widgets/lineeditechoswitcher.h \
    widgets/qbuttonlineedit.h \
    widgets/QPixLineEdit.h \
    widgets/colorbuttonchooser.h \
    widgets/spinboxdelegate.h \
    widgets/styledbar.h \
    widgets/fancyactionbar.h \
    widgets/fancytabwidget.h \
    widgets/minisplitter.h \
    widgets/combowithfancybutton.h \
    widgets/basevalidatinglineedit.h \
    widgets/filenamevalidatinglineedit.h \
    widgets/pathchooser.h \
    pubmeddownloader.h \
    qabstractxmltreemodel.h

SOURCES += global.cpp \
    database.cpp \
    log.cpp \
    updatechecker.cpp \
    messagesender.cpp \
    licenseterms.cpp \
    serializer.cpp \
    randomizer.cpp \
    stylehelper.cpp \
    httpdownloader.cpp \
    widgets/scrollingwidget.cpp \
    widgets/lineeditechoswitcher.cpp \
    widgets/qbuttonlineedit.cpp \
    widgets/colorbuttonchooser.cpp \
    widgets/spinboxdelegate.cpp \
    widgets/styledbar.cpp \
    widgets/fancyactionbar.cpp \
    widgets/fancytabwidget.cpp \
    widgets/minisplitter.cpp \
    widgets/combowithfancybutton.cpp \
    widgets/basevalidatinglineedit.cpp \
    widgets/filenamevalidatinglineedit.cpp \
    widgets/pathchooser.cpp \
    pubmeddownloader.cpp \
    qabstractxmltreemodel.cpp

macx {
    OBJECTIVE_SOURCES += iconbadgealert.mm
    LIBS += -framework Carbon -framework AppKit
} else {
    SOURCES += iconbadgealert.cpp
}

# translators
TRANSLATIONS += $${SOURCES_TRANSLATIONS}/utils_fr.ts \
    $${SOURCES_TRANSLATIONS}/utils_de.ts \
    $${SOURCES_TRANSLATIONS}/utils_es.ts

# resources
#RESOURCES += $${SOURCES_GLOBAL_RESOURCES}/pixmap/svg/fancytoolbutton.svg
