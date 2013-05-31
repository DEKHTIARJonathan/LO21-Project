SOURCES += \
	main.cpp \
	note/note.cpp \
        export/exportstrategy.cpp \
	export/exportstrategynotfoundexception.cpp \
        dbmanager/databasemanager.cpp

HEADERS += \
	note/note.h \
        export/exportstrategy.h \
	export/exportstrategynotfoundexception.h \
        dbmanager/databasemanager.h

FORMS +=

QT += widgets \
      sql
