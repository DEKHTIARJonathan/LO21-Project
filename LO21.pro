SOURCES += \
	main.cpp \
	note/note.cpp \
    export/exportstrategy.cpp \
	export/exportstrategynotfoundexception.cpp \
        databasemanager.cpp \
    note/article.cpp \
    note/document.cpp \
    note/documentindexoutofarrayexception.cpp \
    note/multimedia.cpp

HEADERS += \
	note/note.h \
    export/exportstrategy.h \
	export/exportstrategynotfoundexception.h \
	databasemanager.h \
    note/article.h \
    note/document.h \
    note/documentindexoutofarrayexception.h \
    note/multimedia.h

FORMS +=

QT += widgets \
      sql

