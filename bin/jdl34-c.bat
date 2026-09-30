@echo off
"%~dp0..\exec\jdl34.exe" build --lang c %*
exit /b %ERRORLEVEL%
