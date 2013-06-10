SOURCES += \
    main.cpp \
    export/exportstrategynotfoundexception.cpp \
    note/note.cpp \
    note/article.cpp \
    note/document.cpp \
    note/documentindexoutofarrayexception.cpp \
    note/multimedia.cpp \
    note/image.cpp \
    dbmanager/databasemanager.cpp \
    note/audio.cpp \
    note/video.cpp \
    export/exporthtml.cpp \
    export/exporttex.cpp \
    export/exporttext.cpp \
    notemanager/notesmanager.cpp \
    notefactory/notefactorynotfoundexception.cpp \
    notefactory/generalnotefactory.cpp \
    constants.cpp \
    dbmanager/dbexception.cpp \
    notemanager/notesmanagerexception.cpp \
    export/generalexportfactory.cpp \
    export/exportfactorynotfoundexception.cpp \
    view/mainwindow.cpp \
    export/exportfileexception.cpp \
    export/exportstrategy.cpp \
    view/notesview/articleview.cpp \
    view/notesview/noteview.cpp \
    view/notesview/generalviewfactory.cpp \
    view/notesview/viewfactorynotfoundexception.cpp \
    view/listnoteviewitem.cpp \
    view/workspaceform.cpp \
    view/notesview/imageview.cpp \
    view/notesview/audioview.cpp \
    view/notesview/videoview.cpp \
    view/notesview/documentview.cpp \
    view/notesview/notedocumentview.cpp \
    view/notesview/choosenotedialog.cpp \
    view/trashdialog.cpp \
    view/tagsdialog.cpp

HEADERS += \
    export/exportstrategy.h \
    export/exportstrategynotfoundexception.h \
    note/note.h \
    note/article.h \
    note/document.h \
    note/documentindexoutofarrayexception.h \
    note/multimedia.h \
    note/image.h \
    note/audio.h \
    note/video.h \
    note/classdef.h \
    dbmanager/databasemanager.h \
    export/exporthtml.h \
    export/exporttex.h \
    export/exporttext.h \
    notemanager/notesmanager.h \
    notefactory/notefactorynotfoundexception.h \
    notefactory/generalnotefactory.h \
    constants.h \
    notefactory/interfacenotefactory.h \
    notefactory/notefactory.h \
    dbmanager/dbexception.h \
    notemanager/notesmanagerexception.h \
    export/interfaceexportfactory.h \
    export/exportfactory.h \
    export/generalexportfactory.h \
    export/exportfactorynotfoundexception.h \
    view/mainwindow.h \
    export/exportfileexception.h \
    view/notesview/articleview.h \
    view/notesview/noteview.h \
    view/notesview/generalviewfactory.h \
    view/notesview/interfaceviewfactory.h \
    view/notesview/viewfactory.h \
    view/notesview/viewfactorynotfoundexception.h \
    controller/controller.h \
    view/listnoteviewitem.h \
    view/workspaceform.h \
    view/notesview/imageview.h \
    view/notesview/audioview.h \
    view/notesview/videoview.h \
    view/notesview/documentview.h \
    view/notesview/notedocumentview.h \
    view/notesview/choosenotedialog.h \
    view/trashdialog.h \
    view/tagsdialog.h

FORMS += \
    view/mainwindow.ui \
    view/notesview/articleview.ui \
    view/workspaceform.ui \
    view/notesview/imageview.ui \
    view/notesview/audioview.ui \
    view/notesview/videoview.ui \
    view/notesview/documentview.ui \
    view/notesview/notedocumentview.ui \
    view/notesview/choosenotedialog.ui \
    view/trashdialog.ui \
    view/tagsdialog.ui

QT += widgets \
      sql \
      webkit\
      webkitwidgets\
      network

RESOURCES += \
    ressources/iconlib.qrc
