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
    name = "EFFPACK",
    version = "1.0.0",
    description = "EFFPACK TOOL",
    options = dict(build_exe = buildOptions),
    executables = [
        # tool
        Executable(
            "pack/main.py",
            base = GUI_BASE_APP,
            targetName = "tool" + EXECUTABLE_EXTENSION,
            icon = "pack/data/icons/application_icon.ico"
        ),
        # effect
        Executable(
            "pack/eff/maineff.py",
            base = GUI_BASE_APP,
            targetName = "effpack" + EXECUTABLE_EXTENSION,
            icon = "pack/data/icons/effect_icon.ico"
        ),
        # character
        Executable(
            "pack/char/mainchar.py",
            base = GUI_BASE_APP,
            targetName = "charpack" + EXECUTABLE_EXTENSION,
            icon = "pack/data/icons/char_icon.ico"
        ),
        # terrain
        Executable(
            "pack/terrain/mainter.py",
            base = GUI_BASE_APP,
            targetName = "terpack" + EXECUTABLE_EXTENSION,
            icon = "pack/data/icons/ter_icon.ico"
        )
    ]
)
