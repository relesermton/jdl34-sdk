@echo off
setlocal
"%~dp0jdl34.exe" build --lang cpp %*
exit /b %ERRORLEVEL%
