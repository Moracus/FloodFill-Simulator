@echo off
REM OBJS specifies which files to compile as part of the project
set OBJS=matrix.cpp

REM CC specifies which compiler we're using
set CC=g++

REM INCLUDE_PATHS specifies the additional include paths we'll need
set INCLUDE_PATHS=-I src\include\SDL2

REM LIBRARY_PATHS specifies the additional library paths we'll need
set LIBRARY_PATHS=-L src\lib

REM COMPILER_FLAGS specifies the additional compilation options we're using
REM -w suppresses all warnings
REM -Wl,-subsystem,windows gets rid of the console window
REM set COMPILER_FLAGS=-w -Wl,-subsystem,windows
set COMPILER_FLAGS=-w

REM LINKER_FLAGS specifies the libraries we're linking against
set LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image

REM OBJ_NAME specifies the name of our executable
set OBJ_NAME=matrix

REM This is the target that compiles our executable
%CC% %OBJS% %INCLUDE_PATHS% %LIBRARY_PATHS% %COMPILER_FLAGS% %LINKER_FLAGS% -o %OBJ_NAME%
