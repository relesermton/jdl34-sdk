@echo off
setlocal
"%~dp0jdl34.exe" version %*
exit /b %ERRORLEVEL%
