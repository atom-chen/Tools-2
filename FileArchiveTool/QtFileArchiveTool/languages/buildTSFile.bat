set CUR_DIR=%~dp0
%CUR_DIR:~0,2%  
cd %CUR_DIR%

set OutTS=qt_zh.ts
echo ^<?xml version="1.0" encoding="utf-8"?^> > %OutTS%
echo ^<!DOCTYPE TS^> >> %OutTS%
echo ^<TS^> >> %OutTS%
echo ^</TS^> >> %OutTS%

pause