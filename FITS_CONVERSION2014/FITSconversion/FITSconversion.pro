OTHER_FILES += \
    FITSconversion.pro.user
QT += widgets \
    network


SOURCES += \
    mainwindow.cpp \
    downloader.cpp \
    filepanel.cpp \
    main.cpp \
    urlselectionwindow.cpp

HEADERS += \
    downloader.h \
    filepanel.h \
    mainwindow.h \
    urlselectionwindow.h




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../HKinsertrion/lib/release/ -lCCfits
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../HKinsertrion/lib/debug/ -lCCfits
else:unix: LIBS += -L$$PWD/../HKinsertrion/lib/ -lCCfits

INCLUDEPATH += $$PWD/../HKinsertrion
DEPENDPATH += $$PWD/../HKinsertrion
