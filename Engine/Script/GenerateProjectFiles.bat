@echo off

SET project=%1
SET visualstudio=%2
SET crashdump=%3
SET engine=Engine

echo generate project files...

if not exist %crashdump% (
    echo can't find %crashdump% directory...
    echo generate %crashdump% directory...
    mkdir %crashdump%
)

if exist %project% (
	echo already exist %project%...
)

echo run premake5.exe...
%engine%\\Bin\\premake5.exe %visualstudio%
start %project%\\%project%.sln
PAUSE