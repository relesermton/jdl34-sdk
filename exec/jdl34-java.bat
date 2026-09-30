@echo off
setlocal
"%~dp0jdl34.exe" build --lang java %*
exit /b %ERRORLEVEL%
