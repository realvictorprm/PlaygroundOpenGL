---
title: Build tool change
date: 2017-07-17 21:30:27
tags:
coverImage: https://www.opengl.org/img/opengl_logo.png
---

# Short look into common C++ build tools
Build tools for C++ are still these days a difficult topic. To know them is very important because often you want to run conform with the rest of the world. 

## <img src="https://cmake.org/wp-content/uploads/2014/06/slider-cmake.png" height="50"/> [CMAKE](https://cmake.org) 
<p align="justify">
These days mostly used build tool is definitely _CMAKE_. Heavy usage is seen e.g. with Qt and other big libraries. 
CMAKE in detail consists mainly of a single file called _CMakeLists.txt_ (sometimes some helper script files are added for seperation).
This file describes the library requirements, header requirements, include folders etc. However it's only used to generate the final build script files like _GNU Makefiles_ or _Visual Studio solution files_ through inputing it into the cmake command line tool. In short, sounds like a good tool _but_ the language used to write those description files (cmakelist.txt) is a _weird variation of bash_. Definitely it isn't that comfortable to work with and so some people still prefer other build tools. Last note, using CMAKE requires that the client has CMAKE installed.
</p>

## <img src="https://premake.github.io/premake-logo.png" height="50"/> [Premake](https://premake.github.io) 
<p align="justify">
Another widely used tool is _premake_. Used by big game companies like _Blizzard_ it's definitely a tool to go. In general premake works the same like CMAKE however instead of using a weird variation of bash or other weird and uncomfortable languages it just makes usage of _Lua_. And so the build files are often very easy to write for normal developers because Lua is a widely know language without special knowledge requirements. Easy, simple, nice! Of course _premake_ has some special functions and writings but it's also very easy to understand. Nevertheless, best thing about _premake_ is that it's a lot easier to read compared to _CMAKE_. Unfortunately there are some reasons why _premake_ isn't as much used as _CMAKE_. One of those reasons is the lack of functionality e.g. passing special build command flags for the C++ compiler. Last note, using Premake requires the client _not_ to have it installed. It's often _shipped with the repository_ as you may have noticed with mine.
</p>

## Results
Due to the lack of selecting special C++ language version with Premake I'm pushed to switch the repositories build system to CMAKE. Unfortunately I'm using C++17 features which need special build flags. It's really a bummer, _Premake_ isn't capable of this yet.. _yet_ my friends!

Now let's work on switching the build system!


