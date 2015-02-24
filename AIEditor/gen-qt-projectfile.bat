@echo off

set CUR_DIR=%~dp0
set OUT_PRO=%CUR_DIR%\QtAIEditor\languages\translate.pro

if exist %OUT_PRO% del %OUT_PRO%

echo. > %OUT_PRO%

echo TRANSLATIONS = \ >> %OUT_PRO%
for /r %CUR_DIR%\QtAIEditor\languages %%a in (*.ts) do echo     %%a \ >> %OUT_PRO%
echo. >> %OUT_PRO%


echo FORMS = \ >> %OUT_PRO%
for /r %CUR_DIR%\QtAIEditor %%a in (*.ui) do echo     %%a \ >> %OUT_PRO%
echo. >> %OUT_PRO%

echo SOURCES = \ >> %OUT_PRO%
for /r %CUR_DIR%\QtAIEditor\Src %%a in (*.cpp) do echo     %%a \ >> %OUT_PRO%
echo. >> %OUT_PRO%

echo HEADERS = \ >> %OUT_PRO%
for /r %CUR_DIR%\QtAIEditor\Inc %%a in (*.h) do echo     %%a \ >> %OUT_PRO%
echo. >> %OUT_PRO%
