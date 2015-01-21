SOURCES += \
    main.cpp
QT += widgets

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lCCfits
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lCCfits
else:unix: LIBS += -L$$PWD/lib/ -lCCfits

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
