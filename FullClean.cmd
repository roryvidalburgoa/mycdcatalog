@echo off
@echo Deleting all CVS, BIN and OBJ folders...
for /d /r . %%d in (bin,obj,.vs,CVS) do @if exist "%%d" rd /s /q "%%d"
@echo CVS, BIN and OBJ folders successfully deleted :) Close the window.
pause > nul

FORFILES /S /M *.bak /C "cmd /c DEL @file"
