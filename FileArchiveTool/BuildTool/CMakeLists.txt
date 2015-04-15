project(QtFileArchiveTool)

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
	file(GLOB SRCS_FILES Src/*.h Src/*.cpp)

	#these files need build moc files
    SET(MOC_FILES
        ./Src/MainWindow.h
		./Src/LogWidget.h
		./Src/ProjectWidget.h
		./Src/CenterTabWidget.h
    )
	
	SET(QRC_FILES ./Res/Qrc.qrc)
	
	qt5_wrap_cpp(MOC_SRCS ${MOC_FILES})
    qt5_wrap_ui(UI_SRCS ${UI_FILES})
	qt5_add_resources(QRC_SRCS ${QRC_FILES})

    source_group("Moc Files" FILES ${MOC_SRCS})
    source_group("Ui Files" FILES ${UI_SRCS} ${UI_FILES})
	source_group("Qrc Files" FILES ${QRC_SRCS} ${QRC_FILES})
	
	file(GLOB RC_FILES ./Res/*.rc)
	source_group("Rc Files" FILES ${RC_FILES})
	
    source_group("Source Files" FILES ${SRCS_FILES})

	set(BOOST_ROOT $ENV{BOOST_ROOT})
	set(Boost_USE_STATIC_LIBS   ON)
	set(Boost_USE_MULTITHREADED ON)
	find_package(Boost
             1.57.0
             COMPONENTS thread
             REQUIRED)

    # if we don't include this CMake will not include ui headers properly:
    include_directories(${CMAKE_CURRENT_BINARY_DIR} ./Src ../FileArchiveTool/Src ../FastDelegate_src ${QT_BINARY_DIR}/../include ${Boost_INCLUDE_DIRS}  ../lzma920/C ../icu4c-54_1-src/include)
	
	link_directories(${QT_BINARY_DIR}/../lib ${Boost_LIBRARY_DIRS} ../icu4c-54_1-src/lib64)
	
	ADD_DEFINITIONS(-DFILEARCHIVETOOL_DLL)
	
    set(ALLSRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES})

    ADD_EXECUTABLE(QtFileArchiveTool WIN32 ${ALLSRCS})

    set_target_properties(QtFileArchiveTool PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
	
	TARGET_LINK_LIBRARIES(QtFileArchiveTool ${Qt5Widgets_LIBRARIES} LzmaLib FileArchiveTool icuucd)

	add_dependencies(QtFileArchiveTool FileArchiveTool LzmaLib)
	
endif(NOT Qt5Widgets_FOUND)