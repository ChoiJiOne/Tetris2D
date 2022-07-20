@echo off

echo Generate Project Files ...

if exist Tetris2D (
	echo Remove Legacy Folder ...
	rmdir /s /q Tetris2D
)

mkdir Tetris2D
premake5.exe vs2019
PAUSE
