function IncludeFiles()
   files {
      "%{source_path}/*",

      "%{framework_path}/*",

      "%{third_party_path}/Include/Json/*",
      "%{third_party_path}/Include/SDL2/*",
      "%{third_party_path}/Include/STB/*",
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
      "%{third_party_path}/Debug/SDL2d.lib",
      "%{third_party_path}/Debug/SDL2maind.lib"
   }
end

function LinkStaticLibraryInRelease()
   links {
      "%{third_party_path}/Release/SDL2.lib",
      "%{third_party_path}/Release/SDL2main.lib"
   }
end

workspace "Tetris1.0"

   configurations { "Debug", "Release" }
   platforms { "Win64" }


   location "Tetris1.0"
   

   source_path="%{wks.location}/../Source"
   framework_path="%{wks.location}/../Framework"
   third_party_path="%{wks.location}/../ThirdParty"

   
   project "Tetris1.0"
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


