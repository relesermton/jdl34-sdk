@echo off
"%~dp0..\exec\jdl34.exe" probe %*
exit /b %ERRORLEVEL%
