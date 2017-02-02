FUNCTION(Log arg)
	message(STATUS "${arg}")
ENDFUNCTION()

FUNCTION(Warn arg)
	message(STATUS "${arg}")
ENDFUNCTION()

FUNCTION(Error arg)
	message(STATUS "${arg}")
ENDFUNCTION()