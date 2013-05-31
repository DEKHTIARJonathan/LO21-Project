SOURCES += \
	main.cpp \
	export/exportstrategy.cpp \
	export/exportstrategynotfoundexception.cpp \
	note/note.cpp \
    note/article.cpp \
    note/document.cpp \
    note/documentindexoutofarrayexception.cpp \
    note/multimedia.cpp
	dbmanager/databasemanager.cpp

HEADERS += \
	export/exportstrategy.h \
	export/exportstrategynotfoundexception.h \
	note/note.h \
    note/article.h \
    note/document.h \
    note/documentindexoutofarrayexception.h \
	note/multimedia.h \
	dbmanager/databasemanager.h

FORMS +=

QT += widgets \
      sql

