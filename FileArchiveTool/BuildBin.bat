echo on
rem @echo off
set base_dir=%~dp0
%base_dir:~0,2%

cd %base_dir%

set GENERATOR="Visual Studio 12 2013 Win64"
set DEVENV="F:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe"

if exist %base_dir%build rd /s /q %base_dir%build
mkdir %base_dir%build

cd %base_dir%build

if exist %base_dir%BatPath.bat call %base_dir%BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G%GENERATOR% -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_INSTALL_PREFIX:PATH=%base_dir%build %base_dir%
) else (
	echo set CMAKEPATH="D:\Program Files (x86)\cmake-3.1.3-win32-x86\bin\cmake.exe" > %base_dir%BatPath.bat
	echo set DEVENV="F:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" >> %base_dir%BatPath.bat
	echo Error CMAKEPATH not define
)

cd %base_dir%

%DEVENV% %base_dir%build\FileArchiveTool.sln /build "Debug" /project "INSTALL"

pause