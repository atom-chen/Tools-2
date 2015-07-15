project(QtGameEditor)

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
		./Src/MyGraphicsScene.h
		./Src/MyGraphicsScene.cpp
		./Src/BoardHexagon.h
		./Src/BoardHexagon.cpp
		./Src/DraggableItemBase.h
		./Src/DraggableItemBase.cpp
		./Src/DraggableItemWidget.h
		./Src/DraggableItemWidget.cpp
		./Src/MyGraphicsView.h
		./Src/MyGraphicsView.cpp
		./Src/BezierCurveItem.h
		./Src/BezierCurveItem.cpp
		./Src/DragDropSys.h
		./Src/DragDropSys.cpp
		./Src/QtGameEditorSys.h
		./Src/QtGameEditorSys.cpp
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
		./Src/MyGraphicsScene.h
		./Src/DraggableItemWidget.h
		./Src/MyGraphicsView.h
		./Src/ExplorerWidget.h
		./Src/TreeWidget/MyBasicTreeView.h
		./Src/TreeWidget/MyBasicTreeWidget.h
		./Src/ListWidget/MyBasicListWidget.h
		./Src/TabWidget/MyTabBar.h
		./Src/TabWidget/MyTabMainWindow.h
		./Src/TabWidget/MyTabSubWidgetFrame.h
		./Src/TabWidget/MyTabSubWidgetBase.h
		./Src/TabWidget/ActionEffectEditor/ActionEffectEditor.h
		./Src/TabWidget/ActionEffectEditor/NodeDockWidget.h
		./Src/TabWidget/ActionEffectEditor/BtnListWidget.h
		./Src/TabWidget/ActionEffectEditor/MyScrollAreaWidget.h
		./Src/TabWidget/ActionEffectEditor/DragDropItemWidget.h
		./Src/TabWidget/MyTabWidget.h
		./Src/TestWidget/TestQScrollArea1F.h
		./Src/TestWidget/TestQSplitter.h
    )
	
	SET(QRC_FILES ./Res/Qrc.qrc)
	
	set(TREE_WIDGET
		./Src/TreeWidget/MyCheckFileSystemModel.h
		./Src/TreeWidget/MyCheckFileSystemModel.cpp
		./Src/TreeWidget/MyBasicFileSystemModel.h
		./Src/TreeWidget/MyBasicFileSystemModel.cpp
		./Src/TreeWidget/MyDirModel.h
		./Src/TreeWidget/MyDirModel.cpp
		./Src/TreeWidget/MyBasicTreeView.h
		./Src/TreeWidget/MyBasicTreeView.cpp
		./Src/TreeWidget/MyBasicMVCTreeWidget.h
		./Src/TreeWidget/MyBasicMVCTreeWidget.cpp
		./Src/TreeWidget/MyBasicTreeWidget.h
		./Src/TreeWidget/MyBasicTreeWidget.cpp
		./Src/TreeWidget/MyBasicTreeWidgetItem.h
		./Src/TreeWidget/MyBasicTreeWidgetItem.cpp
		./Src/TreeWidget/MyBasicTreeWidgetItemData.h
		./Src/TreeWidget/MyBasicTreeWidgetItemData.cpp
	)
	
	set(LIST_WIDGET_SRC
		./Src/ListWidget/MyBasicListWidget.h
		./Src/ListWidget/MyBasicListWidget.cpp
		./Src/ListWidget/MyBasicListWidgetItem.h
		./Src/ListWidget/MyBasicListWidgetItem.cpp
		./Src/ListWidget/MyBasicListWidgetItemData.h
		./Src/ListWidget/MyBasicListWidgetItemData.cpp
	)
	
	set(TAB_WIDGET_SRC
		./Src/TabWidget/MyTabBar.h
		./Src/TabWidget/MyTabBar.cpp
		./Src/TabWidget/MyTabMainWindow.h
		./Src/TabWidget/MyTabMainWindow.cpp
		./Src/TabWidget/MyTabSubWidgetFrame.h
		./Src/TabWidget/MyTabSubWidgetFrame.cpp
		./Src/TabWidget/MyTabWidget.h
		./Src/TabWidget/MyTabWidget.cpp
		./Src/TabWidget/TabWidgetMgr.h
		./Src/TabWidget/TabWidgetMgr.cpp
		./Src/TabWidget/MyTabSubWidgetBase.h
		./Src/TabWidget/MyTabSubWidgetBase.cpp
	)
	
	set(MISC_SRC
		./Src/Misc/UtilEncode.h
		./Src/Misc/UtilEncode.cpp
	)
	
	set(NODE_WIDGET_SRC
		./Src/NodeWidget/NodeWidgetBase.h
		./Src/NodeWidget/NodeWidgetBase.cpp
		./Src/NodeWidget/NodeWidgetMgr.h
		./Src/NodeWidget/NodeWidgetMgr.cpp
		./Src/NodeWidget/TestNodeWidget.h
		./Src/NodeWidget/TestNodeWidget.cpp
	)
	
	set(ACTION_EFFECT_EDITOR_SRC
		./Src/TabWidget/ActionEffectEditor/ActionEffectEditor.h
		./Src/TabWidget/ActionEffectEditor/ActionEffectEditor.cpp
		./Src/TabWidget/ActionEffectEditor/NodeDockWidget.h
		./Src/TabWidget/ActionEffectEditor/NodeDockWidget.cpp
		./Src/TabWidget/ActionEffectEditor/BtnListWidget.h
		./Src/TabWidget/ActionEffectEditor/BtnListWidget.cpp
		./Src/TabWidget/ActionEffectEditor/MyScrollAreaWidget.h
		./Src/TabWidget/ActionEffectEditor/MyScrollAreaWidget.cpp
		./Src/TabWidget/ActionEffectEditor/DragDropItemWidget.h
		./Src/TabWidget/ActionEffectEditor/DragDropItemWidget.cpp
		./Src/TabWidget/ActionEffectEditor/RecvDropRectItem.h
		./Src/TabWidget/ActionEffectEditor/RecvDropRectItem.cpp
	)
	
	set(TEST_WIDGET_SRC
		./Src/TestWidget/TestQScrollArea1F.h
		./Src/TestWidget/TestQScrollArea1F.cpp
		./Src/TestWidget/TestQSplitter.h
		./Src/TestWidget/TestQSplitter.cpp
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
	source_group("TreeWidget" FILES ${TREE_WIDGET})
	source_group("Misc" FILES ${MISC_SRC})
	source_group("ListWidget" FILES ${LIST_WIDGET_SRC})
	source_group("TabWidget" FILES ${TAB_WIDGET_SRC})
	source_group("NodeWidget" FILES ${NODE_WIDGET_SRC})
	source_group("TabWidget\\ActionEffectEditor" FILES ${ACTION_EFFECT_EDITOR_SRC})
	source_group("TestWidget" FILES ${TEST_WIDGET_SRC})

    # if we don't include this CMake will not include ui headers properly:
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    include_directories(./Src)
	include_directories(./Src/TreeWidget)
	include_directories(./Src/ListWidget)
	include_directories(./Src/TabWidget)
	include_directories(./Src/TabWidget/ActionEffectEditor)
	include_directories(./Src/NodeWidget)
	include_directories(./Src/TestWidget)
	include_directories(./Src/Misc)
	include_directories(../GameEditor/Src)
	include_directories(../GameEditor/Src/TreeData)
	include_directories(../GameEditor/Src/ListData)
	include_directories(../GameEditor/Src/TabData)
	include_directories(../GameEditor/Src/NodeData)
	include_directories(../GameEditor/Src/SkillAction)
	include_directories( ../Extern/tinyxml)
	include_directories(${QT_BINARY_DIR}/../include)
	
	link_directories(${QT_BINARY_DIR}/../lib)
	
	ADD_DEFINITIONS(-DGAMEEDITOR_DLL)
	
    set(ALLSRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES} ${TREE_WIDGET} ${MISC_SRC} ${LIST_WIDGET_SRC} ${TAB_WIDGET_SRC} ${NODE_WIDGET_SRC} ${ACTION_EFFECT_EDITOR_SRC} ${TEST_WIDGET_SRC})

    ADD_EXECUTABLE(QtGameEditor WIN32 ${ALLSRCS})

    set_target_properties(QtGameEditor PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
	
	TARGET_LINK_LIBRARIES(QtGameEditor ${Qt5Widgets_LIBRARIES} GameEditor tinyxml)
	
	add_dependencies(QtGameEditor GameEditor tinyxml)
	
endif(NOT Qt5Widgets_FOUND)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Config)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Config)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Config DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Config)