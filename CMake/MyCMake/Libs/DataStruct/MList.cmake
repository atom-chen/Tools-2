#--------------------------
# List 操作
#--------------------------

FUNCTION(GetListLength arg)
	set(argvLen 0)
	
	if(${ARGC} NOT EQUAL 1)
		Log("GetListLength, ARGC not equal 1")
	else()
		list(LENGTH ${ARGV0} ${argvLen})
	endif()
	return(${argvLen})
ENDFUNCTION

FUNCTION(GetListItemByIndex arg)
	set(argvValue)
	
	if(${ARGC} NOT EQUAL 2)
		Log("GetListItemByIndex, ARGC not equal 2")
	else()
		set(_list ${ARGV0})
		set(_index ${ARGV1})
		set
		list(GET ARGV ${i} argvValue) 
	endif()
	return(${argvValue})
ENDFUNCTION