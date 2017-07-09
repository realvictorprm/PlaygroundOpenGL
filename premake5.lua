-- premake5.lua
include "helper.lua"

workspace "GraphicsProgramming"
    configurations { "Debug", "Release" }
	architecture "x86_64"
	language "C++"
	buildGLFW()
	buildAssimp()

project "FirstChapter"
	kind "ConsoleApp"
	location "src/FirstChapter"
	debugdir "src/FirstChapter/bin/%{cfg.longname}"
	targetdir "src/FirstChapter/bin/%{cfg.longname}"
	files {
		"src/FirstChapter/**.h", 
		"src/FirstChapter/**.c", 
		"src/FirstChapter/**.cpp", 
		"src/FirstChapter/**.hpp",
		"src/shaders/FirstChapter/*.*"}
		
	includeGLFW()
	linkGLFW()
	includeGLM()
	includeAndAddGlad()	
	includeOGLPlus()
	includeAndLinkToAssimp()
	
	if (os.is("Windows")) then
		links { "OpenGL32" }
	else
		links { "GL" }
		libdirs { os.findlib("GL") }
	end
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"