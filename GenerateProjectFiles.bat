@echo off

echo Generate Project Files ...

if exist Tetris1.0 (
	echo Remove Legacy Folder ...
	rmdir /s /q Tetris1.0
)

mkdir Tetris1.0
premake5.exe vs2019
PAUSE
