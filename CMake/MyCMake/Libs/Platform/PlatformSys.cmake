###################################
# 平台检测
###################################

# 变量定义
SET(MY_WIN32 False)
SET(MY_APPLE False)
SET(MY_UNIX False)
SET(MY_UNIX False)
SET(MY_LINUX False)
SET(MY_ANDROID False)

SET(MY_DEBUG_mode False)

IF(WIN32)
	MESSAGE(STATUS "Now is windows")
	SET(MY_WIN32 True)
ELSEIF(APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
	SET(MY_APPLE True)
ELSEIF(UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's. Including aPPLE os x  and CygWin")
	SET(MY_UNIX True)
ELSEIF(LINUX)
	SET(MY_LINUX True)
ELSEIF(ANDROID)
	SET(MY_ANDROID True)
ENDIF()

IF(DEBUG_mode)
    SET(MY_DEBUG_mode True)
ENDIF()

FUNCTION(IsWin32 arg)
	# return ${MY_WIN32}
	return(${MY_WIN32})
ENDFUNCTION()

FUNCTION(IsApple arg)
	return(${MY_APPLE})
ENDFUNCTION() 

FUNCTION(IsUnix arg)
	return(${MY_UNIX})
ENDFUNCTION() 

FUNCTION(IsLinux arg)
	return(${MY_LINUX})
ENDFUNCTION() 

FUNCTION(IsAndroid arg)
	return(${MY_ANDROID})
ENDFUNCTION() 