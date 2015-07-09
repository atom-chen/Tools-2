project(QtAIEditor)

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

if (DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})
else ()
    message (FATAL_ERROR "ERROR: Environment variable QTDIR is not set. Please locate your Qt folder MY_QT5_DIR.")
endif ()

#set (CMAKE_MODULE_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64")
set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

find_package(Qt5Widgets REQUIRED)

if(NOT Qt5Widgets_FOUND)
    message(SEND_ERROR "Failed to find Qt 5.0.0 or greater.")
else(NOT Qt5Widgets_FOUND)
    set(CMAKE_PACKAGE_QTGUI TRUE)

    file(GLOB UI_FILES *.ui)

    set(SRCS_FILES
		./Src/QtIncAll.h
	    ./Src/Main.cpp
		./Src/MainWindow.h
        ./Src/MainWindow.cpp
		./Src/LogWidget.h
		./Src/LogWidget.cpp
		./Src/ProjectWidget.h
		./Src/ProjectWidget.cpp
		./Src/CenterTabWidget.h
		./Src/CenterTabWidget.cpp
		./Src/DragWidget.h
		./Src/DragWidget.cpp
		./Src/DraggablePiece.h
		./Src/DraggablePiece.cpp
		./Src/GraphicsScene.h
		./Src/GraphicsScene.cpp
		./Src/BoardHexagon.h
		./Src/BoardHexagon.cpp
		./Src/DraggableItemBase.h
		./Src/DraggableItemBase.cpp
		./Src/DraggableItemWidget.h
		./Src/DraggableItemWidget.cpp
		./Src/GraphicsView.h
		./Src/GraphicsView.cpp
		./Src/BezierCurveItem.h
		./Src/BezierCurveItem.cpp
		./Src/DragDropSys.h
		./Src/DragDropSys.cpp
		./Src/QtAIEditorSys.h
		./Src/QtAIEditorSys.cpp
		./Src/BuildFactory.h
		./Src/BuildFactory.cpp
		./Src/ExplorerWidget.h
		./Src/ExplorerWidget.cpp
    )

	#these files need build moc files
    SET(MOC_FILES
        ./Src/MainWindow.h
		./Src/LogWidget.h
		./Src/ProjectWidget.h
		./Src/CenterTabWidget.h
		./Src/DragWidget.h
		./Src/GraphicsScene.h
		./Src/DraggableItemWidget.h
		./Src/GraphicsView.h
		./Src/ExplorerWidget.h
		./Src/TreeWidget/MyBasicTreeView.h
    )
	
	SET(QRC_FILES ./Res/Qrc.qrc)
	
	set(PROJECT_WIDGET_DATA_FILES
		./Src/ProjectWidget/ProjectWidgetItemBase.h
		./Src/ProjectWidget/ProjectWidgetItemBase.cpp
	)
	
	set(TREE_WIDGET
		./Src/TreeWidget/MyCheckFileSystemModel.h
		./Src/TreeWidget/MyCheckFileSystemModel.cpp
		./Src/TreeWidget/MyBasicFileSystemModel.h
		./Src/TreeWidget/MyBasicFileSystemModel.cpp
		./Src/TreeWidget/MyDirModel.h
		./Src/TreeWidget/MyDirModel.cpp
		./Src/TreeWidget/MyBasicTreeView.h
		./Src/TreeWidget/MyBasicTreeView.cpp
		./Src/TreeWidget/MyBasicTreeWidget.h
		./Src/TreeWidget/MyBasicTreeWidget.cpp
	)
	
	set(LIST_WIDGET_SRC
		./Src/ListWidget/MyBasicListWidget.h
		./Src/ListWidget/MyBasicListWidget.cpp
	)
	
	set(MISC_SRC
		./Src/Misc/UtilEncode.h
		./Src/Misc/UtilEncode.cpp
	)
	
	qt5_wrap_cpp(MOC_SRCS ${MOC_FILES})
    qt5_wrap_ui(UI_SRCS ${UI_FILES})
	qt5_add_resources(QRC_SRCS ${QRC_FILES})

    source_group("Moc Files" FILES ${MOC_SRCS})
    source_group("Ui Files" FILES ${UI_SRCS} ${UI_FILES})
	source_group("Qrc Files" FILES ${QRC_SRCS} ${QRC_FILES})
	
	file(GLOB RC_FILES ./Res/*.rc)
	source_group("Rc Files" FILES ${RC_FILES})
	
    source_group("Base" FILES ${SRCS_FILES})
	source_group("ProjectWidget" FILES ${PROJECT_WIDGET_DATA_FILES})
	source_group("TreeWidget" FILES ${TREE_WIDGET})
	source_group("Misc" FILES ${MISC_SRC})
	source_group("ListWidget" FILES ${LIST_WIDGET_SRC})

    # if we don't include this CMake will not include ui headers properly:
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    include_directories(./Src)
	include_directories(./Src/ProjectWidget)
	include_directories(./Src/TreeWidget)
	include_directories(./Src/ListWidget)
	include_directories(./Src/Misc)
	include_directories(../AIEditor/Src)
	include_directories(../AIEditor/Src/ProjectData)
	include_directories(${QT_BINARY_DIR}/../include)
	
	link_directories(${QT_BINARY_DIR}/../lib)
	
	ADD_DEFINITIONS(-DAIEDITOR_DLL)
	
    set(ALLSRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES} ${PROJECT_WIDGET_DATA_FILES} ${TREE_WIDGET} ${MISC_SRC} ${LIST_WIDGET_SRC})

    ADD_EXECUTABLE(QtAIEditor WIN32 ${ALLSRCS})

    set_target_properties(QtAIEditor PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
	
	TARGET_LINK_LIBRARIES(QtAIEditor ${Qt5Widgets_LIBRARIES} AIEditor)
	
	add_dependencies(QtAIEditor AIEditor)
	
endif(NOT Qt5Widgets_FOUND)