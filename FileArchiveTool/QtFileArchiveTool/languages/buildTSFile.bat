set CUR_DIR=%~dp0
::%CUR_DIR:~0,2%  
::cd %CUR_DIR%

set OutTS=qt_zh.ts
echo ^<?xml version="1.0" encoding="utf-8"?^> > %CUR_DIR%%OutTS%
echo ^<!DOCTYPE TS^> >> %CUR_DIR%%OutTS%
echo ^<TS^> >> %CUR_DIR%%OutTS%
echo ^</TS^> >> %CUR_DIR%%OutTS%

pause