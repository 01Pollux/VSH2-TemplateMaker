workspace "VSH2-TemplateMaker"
   configurations { "Debug", "Release" }

project "VSH2-TemplateMaker"
   kind "ConsoleApp"
   language "C++"
   files { "**.h", "**.cpp" }

   architecture "x86_64"
   cppdialect "C++17"

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"