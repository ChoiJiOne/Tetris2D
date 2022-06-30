-- 소스 파일 추가
function IncludeFiles()
   files {
      "%{source_path}/*",

      "%{third_party_path}/Include/SDL2/*",
      "%{third_party_path}/Include/STB/*",
   }
end


-- 헤더 파일 경로 추가
function IncludeDirs()
   includedirs {
      "%{source_path}",

      "%{third_party_path}/Include",
   }
end


-- Debug 모드에 정적 라이브러리 추가
function LinkStaticLibraryInDebug()
   links {
      "%{third_party_path}/Debug/SDL2d.lib",
      "%{third_party_path}/Debug/SDL2maind.lib",
   }
end

-- Release 모드에 정적 라이브러리 추가
function LinkStaticLibraryInRelease()
   links {
      "%{third_party_path}/Release/SDL2.lib",
      "%{third_party_path}/Release/SDL2main.lib",
   }
end

-- Tetris2D 프로젝트 설정
workspace "Tetris2D"

   configurations { "Debug", "Release" }
   platforms { "Win64" }

   location "Tetris2D"
   
   source_path="%{wks.location}/../Source"
   third_party_path="%{wks.location}/../ThirdParty"

   project "Tetris2D"
      kind "ConsoleApp"
      language "C++"

      IncludeFiles()
      IncludeDirs()

      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"
         debugdir "%{third_party_path}/Debug"

         LinkStaticLibraryInDebug()

      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"
         debugdir "%{third_party_path}/Release"

         LinkStaticLibraryInRelease()


