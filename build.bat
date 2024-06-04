@echo off
setlocal

if "%Platform%" neq "x64" (
    echo ERROR: Platform is not "x64" - please run this from the MSVC x64 native tools command prompt.
    exit /b 1
)

cd %~dp0
if not exist build mkdir build
cd build

if "%1" neq "" (
	echo Illegal number of arguments^, expected^: build
	goto end
)

cl /nologo /Od /Oi /Zo /Z7 /RTC1 /W3 ..\src\main.c /link /subsystem:windows /out:clst.exe /pdb:clst.pdb /incremental:no /opt:icf /opt:ref gdi32.lib user32.lib

:end
endlocal
