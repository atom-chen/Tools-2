@echo off
rem echo on
::cls
set base_dir=%~dp0
%base_dir:~0,2%
cd %base_dir%

::echo %base_dir%

for /r %base_dir% %%i in (__pycache__ pycache _pycache_) do if exist %%i rmdir /s/q "%%i"
if exist %base_dir%build rd /s /q %base_dir%build

rem pause