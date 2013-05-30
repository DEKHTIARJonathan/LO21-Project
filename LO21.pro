SOURCES += \
	main.cpp \
	note/note.cpp \
    export/exportstrategy.cpp \
	export/exportstrategynotfoundexception.cpp \
	databasemanager.cpp

HEADERS += \
	note/note.h \
    export/exportstrategy.h \
	export/exportstrategynotfoundexception.h \
	databasemanager.h

FORMS +=

QT += widgets \
      sql
