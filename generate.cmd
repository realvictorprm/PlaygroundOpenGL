@echo off
set cmd="premake/premake5.exe"
goto menu

:menu
echo Build Project Generator:
echo.
echo [0] Clean
echo [1] Visual C++ 2015
echo [2] Visual C++ 2017
echo.
echo %cmd%

:choice
set /P C="Choice: "
if "%C%"=="2" goto vs2017
if "%C%"=="1" goto vs2015
if "%C%"=="0" goto clean


:clean
%cmd% --file=premake5.lua clean
goto quit

:vs2015
%cmd% --file=premake5.lua vs2015
goto quit

:vs2017
%cmd% --file=premake5.lua vs2017
goto quit

:quit
pause
:end