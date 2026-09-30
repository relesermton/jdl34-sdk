@echo off
setlocal
"%~dp0jdl34.exe" build %*
exit /b %ERRORLEVEL%
