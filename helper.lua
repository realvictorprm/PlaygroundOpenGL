
function progress(total, current)
  local ratio = current / total;
  ratio = math.min(math.max(ratio, 0), 1);
  local percent = math.floor(ratio * 100);
  print("Download progress (" .. percent .. "%/100%)")
end

function buildGLFW()
	local dir = os.getcwd()
	os.chdir("external/glfw")
	if(os.is("Windows")) then
		os.execute("cmake -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -G \"Visual Studio 15 2017 Win64\"")
		os.execute("msbuild GLFW.sln /p:Configuration=Release")
	else
		os.execute("cmake -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -G \"Unix Makefiles\"")
		os.execute("make")
	end
	os.chdir(dir)
end
	
function includeGLFW()
	includedirs "external/glfw/include/GLFW"
end

function linkGLFW()
	if(os.is("Windows")) then
		links "external/glfw/src/Release/glfw3.lib"
	else
		links "external/glfw/src/Release/libglfw3.so"
	end
end

function includeGLM()
	includedirs "external/glm/glm"
end

function includeOGLPlus()
	includedirs "deps/"
end

function includeAndAddGlad()
	includedirs "deps/glad_static_generated/include"
	files "deps/glad_static_generated/src/glad.c"
end