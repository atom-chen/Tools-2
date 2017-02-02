###################################
# 必须加载的模块
###################################

# 脚本加载模块
FUNCTION(LoadModule arg)
	if(${ARGC} EQUAL 1)
		message(STATUS, "LoadModule, param num is ${ARGC}, param is ${ARGV}")
		list(GET ARGV 0 argv_value)
		message(STATUS, "LoadModule, argv_value is ${argv_value}")
		include(${argv_value})
	else()
		message(FATAL_ERROR, "LoadModule, param num is ${ARGC}, param is ${ARGV}")
	endif()
ENDFUNCTION()

###################################
# 模块路径设置
###################################
FUNCTION(SetCMakeModulePath arg)
	message(STATUS, "SetCMakeModulePath, CMAKE_MODULE_PATH before is ${CMAKE_MODULE_PATH}")
	message(STATUS, "SetCMakeModulePath, param num is ${ARGC}, all param is ${ARGV}")
	
	set(index 0)
    
	while(index LESS ${ARGC})
		message(STATUS, "SetCMakeModulePath, index = ${index}, param is ${ARGV${index}}")
		list(GET ARGV ${index} argv_value)
		message(STATUS, "SetCMakeModulePath, argv_value is ${argv_value}")
		# 列表添加不会改变 CMAKE_MODULE_PATH 的内容
		#list(APPEND ${CMAKE_MODULE_PATH} "${argv_value}")
		SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${argv_value})
		
		math(EXPR index "${index} + 1")
	endwhile()
	message(STATUS, "SetCMakeModulePath, CMAKE_MODULE_PATH after is ${CMAKE_MODULE_PATH}")
ENDFUNCTION()