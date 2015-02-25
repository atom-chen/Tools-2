set CUR_DIR=%~dp0
%CUR_DIR:~0,2%  
cd %CUR_DIR%

if exist buildTSFile.bat call buildTSFile.bat

if exist ../../gen-qt-projectfile.bat call ../../gen-qt-projectfile.bat

if exist update.bat	call update.bat

if exist compile.bat call compile.bat

pause