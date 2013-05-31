SOURCES += \
	main.cpp \
	export/exportstrategy.cpp \
	export/exportstrategynotfoundexception.cpp \
	note/note.cpp \
    note/article.cpp \
    note/document.cpp \
    note/documentindexoutofarrayexception.cpp \
    note/multimedia.cpp \
	note/image.cpp \
	dbmanager/databasemanager.cpp \
    note/audio.cpp \
    note/video.cpp

HEADERS += \
	export/exportstrategy.h \
	export/exportstrategynotfoundexception.h \
	note/note.h \
    note/article.h \
    note/document.h \
    note/documentindexoutofarrayexception.h \
	note/multimedia.h \
	dbmanager/databasemanager.h \
    note/image.h \
    note/audio.h \
    note/video.h

FORMS +=

QT += widgets \
      sql

