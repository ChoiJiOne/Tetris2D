@echo off

echo start build script...
SET engine=Engine
SET build=msbuild.exe
SET project=%1
SET option=%2

if not exist %project% (
    echo can't find %project% visual studio solution
    echo generate visual studio solution...
    %engine%\\Bin\\premake5.exe vs2019
)

%build% %project%\\%project%.sln -property:Configuration=%option% -target:Rebuild /p:SkipShaderCompile=true