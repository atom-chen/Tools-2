# -*- coding: utf-8 -*-
'''
打包 exe 脚本
'''
import platform

GUI_BASE_APP = "Console"
CONSOLE_BASE_APP = "Console"

if platform.system() == "Windows":
    GUI_BASE_APP = "Win32GUI"
    EXECUTABLE_EXTENSION = ".exe"

from cx_Freeze import setup, Executable

buildOptions = dict(
	# package include
    packages =
    [
		
    ],
	# file include
    include_files =
    [
       
    ],
	# 
	includes = 
	[
		"re"
	]
)

setup(
    name = "AUTOUPDATE",
    version = "1.0.0",
    description = "AUTOUPDATE TOOL",
    options = dict(build_exe = buildOptions),
    executables = [
        # tool
        Executable(
            "autoupdate/main.py",
            base = GUI_BASE_APP,
            targetName = "tool" + EXECUTABLE_EXTENSION,
            icon = "autoupdate/data/icons/application_icon.ico"
        )
    ]
)
