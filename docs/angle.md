Building Angle Project
======================

If you want to target Windows, then you need to include the angle project dll in your installation package.  A pre-built version of the angle dll is included in this repository; if you want to build the dll yourself, here are my notes on how I got this to work.

## DirectX SDK

To build angle, you need to install the June 2010 DirectX SDK.  The SDK installer did not work on my system.  I needed to follow the the instructions provided in the following page:

[Known Issue: DirectX SDK (June 2010) Setup and the S1023 error](http://blogs.msdn.com/b/chuckw/archive/2011/12/09/known-issue-directx-sdk-june-2010-setup-and-the-s1023-error.aspx)

## VC++ Directories

The angle project wiki includes [a detailed description of the steps needed to build angle](https://code.google.com/p/angleproject/wiki/DevSetup).  The pre-supplied vs project file is for vs 2010. The instructions assume you use vs 2010 express.  The instructions on setting the include path and library paths did not work for me, so I set these under VC++ Directories within the project properties pages of libEGL and libEGLv2.

## Install into seng project

Look in seng_angle\lib for the products of the build.  Place the .lib files into seng\platforms\vs2010\win and the .dll files into seng\working.

Place the angle include folder into seng/angleproject.
