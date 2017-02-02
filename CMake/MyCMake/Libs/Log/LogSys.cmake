FUNCTION(Log arg)
	#message(STATUS, "${ARGV}")
	message(STATUS "${ARGV}")
ENDFUNCTION()

FUNCTION(Warn arg)
	message(SEND_ERROR "${ARGV}")
ENDFUNCTION()

FUNCTION(Error arg)
	#message(FATAL_ERROR, "${ARGV}")
	message(FATAL_ERROR "${ARGV}")
ENDFUNCTION()