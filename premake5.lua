-- Tetris2D 작업 영역입니다.
workspace "Tetris2D"

   -- 빌드 구성 요소입니다.
   configurations { 
      "Debug",
      "Release",
      "Shipping",
   }

   -- 빌드 플랫폼입니다.
   platforms { "Win64" }

   -- 솔루션 경로를 설정합니다.
   location "%{wks.name}"

   -- 엔진 프로젝트의 경로를 설정합니다.
   engine="%{wks.location}/../Engine"

   -- 게임 프로젝트의 경로를 설정합니다.
   game="%{wks.location}/../Game"

   -- 외부 라이브러리 경로를 설정합니다.
   thirdparty="%{engine}/ThirdParty"

   -- 게임 컨텐츠 경로를 설정합니다.
   content="%{game}/Content"

   startproject "Game"

   -- 엔진 프로젝트입니다.
   project "Engine"
        -- 엔진 프로젝트의 종류를 설정합니다.
        kind "StaticLib"

        -- 프로그래밍 언어를 설정합니다.
        language "C++"

        -- C++의 표준을 설정합니다.
        cppdialect "C++17"

        -- 엔진 소스 코드의 include 경로를 추가합니다.
        includedirs {
            "%{engine}",
            "%{engine}/Private",
            "%{engine}/Public",
            "%{engine}/Shader",
            "%{engine}/Script",
            "%{thirdparty}",
        }

        -- 엔진 소스 코드의 file을 추가합니다.
        files {
            "%{engine}/*",
            "%{engine}/Private/*",
            "%{engine}/Public/*",
            "%{engine}/Shader/*",
            "%{engine}/Script/*",
            "%{thirdparty}/miniaudio/*",
            "%{thirdparty}/stb/*",
        }

        -- 엔진 빌드의 구성 요소별 설정을 수행합니다.
        filter "configurations:Debug"
            defines { "DEBUG" }
            runtime  "Debug"
            optimize "Off"
            symbols "On"

            links {
                "Dbghelp.lib",
                "d3d11.lib",
                "dxgi.lib",
                "d3dcompiler.lib",
            }

        filter "configurations:Release"
            defines { "NDEBUG" }
            runtime "Release"
            optimize "On"
            symbols "On"

            links {
                "Dbghelp.lib",
                "d3d11.lib",
                "dxgi.lib",
                "d3dcompiler.lib",
            }

        filter "configurations:Shipping"
            defines { "NDEBUG" }
            runtime "Release"
            optimize "Full"
            symbols "Off"

            links {
                "Dbghelp.lib",
                "d3d11.lib",
                "dxgi.lib",
                "d3dcompiler.lib",
            }

   -- 게임 프로젝트입니다.
   project "Game"

        -- 게임 프로젝트의 종류를 설정합니다.
        kind "WindowedApp"

        -- 프로그래밍 언어를 설정합니다.
        language "C++"

        -- C++의 표준을 설정합니다.
        cppdialect "C++17"

        -- 엔진을 연결합니다.
        links {"Engine"}

        -- 명령행 인수를 설정합니다.
        debugargs {
            "-Dump=%{game}..\\CrashDump\\",
            "-Content=%{game}\\Content\\",
            "-Shader=%{engine}\\Shader\\",
        }

        -- 게임의 소스 코드의 include 경로를 추가합니다.
        includedirs {
            "%{engine}/Private",
            "%{engine}/Public",

            "%{game}/Source/",
            "%{game}/Source/Private",
            "%{game}/Source/Public",
        }

        -- 게임의 소스 코드의 file을 추가합니다.
        files {
            "%{game}/Source/*",
            "%{game}/Source/Private/*",
            "%{game}/Source/Public/*",

            "%{content}/Audio/*",
            "%{content}/Config/*",
            "%{content}/Font/*",
            "%{content}/Texture/*",
        }

        -- 빌드의 구성 요소별 설정을 수행합니다.
        filter "configurations:Debug"
            defines { "DEBUG" }
            runtime  "Debug"
            optimize "Off"
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            runtime "Release"
            optimize "On"
            symbols "On"

        filter "configurations:Shipping"
            defines { "NDEBUG" }
            runtime "Release"
            optimize "Full"
            symbols "Off"