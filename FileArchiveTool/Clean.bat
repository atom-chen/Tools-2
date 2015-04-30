set base_dir=%~dp0
%base_dir:~0,2%
cd %base_dir%

if exist %base_dir%build rd /s /q %base_dir%build

pause