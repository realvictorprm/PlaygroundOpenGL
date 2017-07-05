if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
	premake5-linux-64 gmake
else 
	premake5-osx gmake
fi

