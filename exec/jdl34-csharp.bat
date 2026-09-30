@echo off
setlocal
"%~dp0jdl34.exe" build --lang cs %*
exit /b %ERRORLEVEL%
