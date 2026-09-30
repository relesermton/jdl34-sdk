@echo off
setlocal
"%~dp0jdl34.exe" driver %*
exit /b %ERRORLEVEL%
