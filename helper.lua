
function progress(total, current)
  local ratio = current / total;
  ratio = math.min(math.max(ratio, 0), 1);
  local percent = math.floor(ratio * 100);
  print("Download progress (" .. percent .. "%/100%)")
end

function buildGLFW()
	local dir = os.getcwd()
	os.chdir("submodules/glfw")
	filter "system:windows"
		os.execute("cmake -DBUILD_SHARED_LIBS=OFF -G \"Visual Studio 15 2017 Win64\"")
		os.execute("msbuild GLFW.sln /p:Configuration=Release")
	os.chdir(dir)
end
	
function includeGLFW()
	includedirs "submodules/glfw/include/GLFW"
end

function linkGLFW()
	links "submodules/glfw/src/Release/glfw3.lib"
end

function includeGLM()
	includedirs "submodules/glm/glm"
end

function includeOGLPlus()
	includedirs "deps/"
end

function includeAndAddGlad()
	includedirs "deps/glad_static_generated/include"
	files "deps/glad_static_generated/src/glad.c"
end