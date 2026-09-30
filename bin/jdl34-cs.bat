@echo off
"%~dp0..\exec\jdl34.exe" build --lang cs %*
exit /b %ERRORLEVEL%
