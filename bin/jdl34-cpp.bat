@echo off
"%~dp0..\exec\jdl34.exe" build --lang cpp %*
exit /b %ERRORLEVEL%
