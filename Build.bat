@echo off

echo start build...
SET option=%1

if not exist Tetris2D (
    echo generate visual studio solution...
    Bin\\premake5.exe vs2019
)

msbuild.exe Tetris2D\\Tetris2D.sln -property:Configuration=%option% -target:Rebuild