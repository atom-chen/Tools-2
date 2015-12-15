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
            "Pack/Main.py",
            base = GUI_BASE_APP,
            targetName = "Tool" + EXECUTABLE_EXTENSION,
            icon = "Pack/data/icons/application_icon.ico"
        ),
        # effect
        Executable(
            "Pack/Effect/MainEffect.py",
            base = GUI_BASE_APP,
            targetName = "EffectPack" + EXECUTABLE_EXTENSION,
            icon = "Pack/data/icons/effect_icon.ico"
        ),
        # character
        Executable(
            "Pack/Character/MainCharacter.py",
            base = GUI_BASE_APP,
            targetName = "CharacterPack" + EXECUTABLE_EXTENSION,
            icon = "Pack/data/icons/char_icon.ico"
        ),
        # terrain
        Executable(
            "Pack/Terrain/MainTerrain.py",
            base = GUI_BASE_APP,
            targetName = "TerrainPack" + EXECUTABLE_EXTENSION,
            icon = "Pack/data/icons/ter_icon.ico"
        )
    ]
)
