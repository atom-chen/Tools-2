set base_dir=%~dp0
%base_dir:~0,2%

cd %base_dir%
D:\Python34\python.exe cx_Freezer.py build

rem copy file
if exist %base_dir%build\exe.win-amd64-3.4\Config rd /s /q %base_dir%build\exe.win-amd64-3.4\Config
md %base_dir%build\exe.win-amd64-3.4\Config
xcopy %base_dir%FileDirDiff\Config\*.* %base_dir%build\exe.win-amd64-3.4\Config /s /e /h

rem ren %base_dir%build\exe.win-amd64-3.4\Config\Config_bak.txt %base_dir%build\exe.win-amd64-3.4\Config\Config.txt
ren %base_dir%build\exe.win-amd64-3.4\Config\Config_bak.txt Config.txt

pause