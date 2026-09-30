@echo off
setlocal
"%~dp0jdl34.exe" build --lang c %*
exit /b %ERRORLEVEL%
