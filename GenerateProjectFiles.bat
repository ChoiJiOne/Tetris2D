@echo off

echo Generate Project Files ...

if not exist CrashDump (
    echo can't find CrashDump directory...
    echo generate CrashDump directory...
    mkdir Dump
)

if exist Tetris2D (
	echo already exist Tetris2D...
)

echo run premake5.exe...
Engine\\Bin\\premake5.exe vs2019
start Tetris2D\\Tetris2D.sln
PAUSE