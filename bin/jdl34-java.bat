@echo off
"%~dp0..\exec\jdl34.exe" build --lang java %*
exit /b %ERRORLEVEL%
