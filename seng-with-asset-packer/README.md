Project Setup
=============

After checking out the project code, you need to set the working directory
for debug runs to the working folder in the seng project.  To do this, right
click the win project in the solution explorer window in Visual Studio, then
select Properties.  In the properties window, select the Debugging node
and set the working directory to the following:

   ..\..\..\working

Seng Overview
=============

Seng is the beginning of a video game project that is designed to be run on
practically all systems of interest: Windows, OS X, iOS, Android.  I beleive
it can be run under Linux using Mesa (http://www.mesa3d.org/opengles.html),
but this does not make good use of the GPU.

The core functionality in seng is implemented in C++.  Platform specific 
code is written in a language based on platform: Java on Android, C++ on
Windows, Objective-C on iOS and OS X.  

Game logic and level defining code is written in Lua.  The Lua interpreter 
is built into senj.

The Thing class is the center of the system.  Thing instances (things) are
game objects that are controllable from Lua via an init function that runs
when the object is created.  The init function will generally attach a
controller and set properties to modify the behavior of the thing.  Things
are meant to be everything in the system: levels, npcs, pcs, buttons,
menus, etc.

Project Organization
====================

    csusbdt-seng
	  README.md -- this file
      working -- working directory when running win in debug mode
        libEGL.dll -- required library when running under Windows
        libGLESv2.dll -- required library when running under Windows
		D3DCompiler_43.dll -- required library when running under Windows
		d3dx9_43.dll -- required library when running under Windows
	  src
	    core -- platform independent seng code
		asset -- platform independent seng code for dealing with assets
		snappy -- I extracted this source from the snappy project
	    lua-5.2.1 -- I downlownded this from the Lua web site.
	  platforms
	    vs2010 -- I added angleproject lib files that I built, and included header files
		          (Notes that EGL is platform specific; xcode includes a different version of EGL.)

Building the ANGLE Project
==========================
The Windows executable depends on 2 dlls from the ANGLE project.  The following
explains how I built these dlls.

  Read http://code.google.com/p/angleproject/wiki/DevSetup to see how to build.  
  Open angleproject/src/ANGLE.sln, select Release build, and do the following configuration:
     Open project properties for the libEGL project, and select VC++ directories; 
	 add the following to the include and library paths:
	    $(DXSDK_DIR)\Include
		$(DXSDK_DIR)\Lib\x86
	Do the same for libGLESv2.
	Build.	
  Copy libEGL.dll and libGLESv2.dll from the Release folder to the seng working folder.

