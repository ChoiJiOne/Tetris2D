@echo off

echo Generate Project Files ...

if not exist Dump (
    echo don't exist dump directory...
    mkdir Dump
)

if exist Tetris2D (
	echo already exist Tetris2D...
)

echo run premake5.exe...
Bin\\premake5.exe vs2019
start Tetris2D\\Tetris2D.sln
PAUSE