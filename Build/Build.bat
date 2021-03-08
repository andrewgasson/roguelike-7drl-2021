@echo off
setlocal
call Config.bat

set Includes=^
	-I%IncludePath%\Game^
	-I%IncludePath%\Raylib^
	-I%IncludePath%

set Links=^
	-L.^
	-L%BinaryPath%^
	-L%LibraryPath%^
	-lgdi32^
	-lopengl32^
	-lraylib

set Sources=^
	%SourcePath%\Game\*.c

set Compiler=gcc
set CompilerFlags=-std=c17 -m64 -DPLATFORM_DESKTOP

%Compiler%^
	-o%ExePath%^
	%CompilerFlags%^
	%Includes%^
	%Links%^
	%Sources%

endlocal
