function IncludeFiles()
   files {
      -- 소스 코드 추가
      "%{source_path}/*",
      "%{source_path}/Game/*",

      -- assimp 추가
      "%{third_party_path}/Include/assimp/*",
      "%{third_party_path}/Include/assimp/Compiler/*",

      -- freetype2 추가
      "%{third_party_path}/Include/freetype2/*",
      "%{third_party_path}/Include/freetype2/dlg/*",
      "%{third_party_path}/Include/freetype2/freetype/*",
      "%{third_party_path}/Include/freetype2/freetype/config/*",
      "%{third_party_path}/Include/freetype2/freetype/internal/*",
      "%{third_party_path}/Include/freetype2/freetype/internal/services/*",

      -- glad 추가
      "%{third_party_path}/Include/glad/*",

      -- gflw 추가
      "%{third_party_path}/Include/glfw/*",

      -- glm 추가
      "%{third_party_path}/Include/glm/*",
      "%{third_party_path}/Include/glm/detail/*",
      "%{third_party_path}/Include/glm/ext/*",
      "%{third_party_path}/Include/glm/gtc/*",
      "%{third_party_path}/Include/glm/gtx/*",
      "%{third_party_path}/Include/glm/simd/*",

      -- httplib 추가
      "%{third_party_path}/Include/httplib/*",

      -- imgui 추가
      "%{third_party_path}/Include/imgui/*",

      -- json 추가
      "%{third_party_path}/Include/json/*",

      -- stb 추가
      "%{third_party_path}/Include/stb/*",
   }
end

function IncludeDirs()
   includedirs {
      "%{source_path}",
      "%{third_party_path}/Include",
   }
end

function LinkStaticLibraryInDebug()
   links {
      "%{third_party_path}/Debug/assimp-vc142-mtd.lib",
      "%{third_party_path}/Debug/freetyped.lib",
      "%{third_party_path}/Debug/glfw3.lib",
   }
end

function LinkStaticLibraryInRelease()
   links {
      "%{third_party_path}/Release/assimp-vc142-mt.lib",
      "%{third_party_path}/Release/freetype.lib",
      "%{third_party_path}/Release/glfw3.lib",
   }
end

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
