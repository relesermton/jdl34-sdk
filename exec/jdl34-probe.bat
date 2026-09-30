@echo off
setlocal
"%~dp0jdl34.exe" probe %*
exit /b %ERRORLEVEL%
