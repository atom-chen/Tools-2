rem @echo off
echo on
::cls
set base_dir=%~dp0
%base_dir:~0,2%
cd %base_dir%

set ToolSet=%base_dir%
set PyLibs=%base_dir%../../PyLibs/src
set PYTHONPATH=%PYTHONPATH%;%ToolSet%;%PyLibs%

set Python=D:\ProgramFiles\Python\Python35\python.exe

rem enter exe path
cd QtToolSet
%Python% ./Main.py

pause