-- premake5.lua
include "helper.lua"

workspace "GraphicsProgramming"
	configurations { "Debug", "Release" }
	architecture "x86_64"
	language "C++"
	buildGLFW()

project "FirstChapter"
	kind "ConsoleApp"
	location "src/FirstChapter"
	debugdir "src/FirstChapter/bin/%{cfg.longname}"
	targetdir "src/FirstChapter/bin/%{cfg.longname}"
	files {
		"src/FirstChapter/*.h", 
		"src/FirstChapter/*.c", 
		"src/FirstChapter/*.cpp", 
		"src/FirstChapter/*.hpp",
		"src/shaders/FirstChapter/*.*"}
		
	includeGLFW()
	linkGLFW()
	
	includeGLM()
	includeAndAddGlad()	
	includeOGLPlus()
	
	filter { "system:windows" }
		links { "OpenGL32" }
	
	filter { "system:not windows" }
		links { "GL" }
		libdirs { os.findlib("GL") }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"