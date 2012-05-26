Overview {#index}
--------

The src folder contains all platform-indenpendent C++ code.

The platforms folder contains all platform-dependent code.  
Visual Studio and XCode project files are stored in here as well.

This project uses the ANGLE project to enable development of OpenGL ES 2.0 code on Windows.

TODO
----

- Develop iOS project in XCode.
- Develop Android project in Eclipse.
- Read [Hello Triangle: An OpenGL ES 2.0 Example](http://www.khronos.org/assets/uploads/books/openglr_es_20_programming_guide_sample.pdf).
- Investigate [OpenSL ES](http://www.khronos.org/opensles/) adio acceleration API. 
  (It's a part of Android.)
- See [Google I/O 2011: Bringing C and C++ Games to Android](http://www.youtube.com/watch?v=5yorhsSPFG4).
  
Quick Links
-----------

- [OpenGL ES 2.0 Reference Pages](http://www.khronos.org/opengles/sdk/docs/man/)
- [EGL Specification](http://www.khronos.org/registry/egl/specs/eglspec.1.4.20110406.pdf)
- [Doxygen manual](file:///C:/Program%20Files/doxygen/html/markdown.html).
- [More links ...](@ref links)

Notes
-----

- For precompiled headers, Read (http://msdn.microsoft.com/en-us/library/2yzw0wyd.aspx) and (http://msdn.microsoft.com/en-us/library/5t8yz59b.aspx)
- Use (or discard) ErrorExit in main.cpp.
- Add XCode section to [Project Setup](@ref setup).
- Test on iPad.
- For IDE, see: http://stackoverflow.com/questions/143939/whats-a-good-ide-to-use-for-lua
- See http://www.luafaq.org/ for extensive unofficial faq
- See http://matthewwild.co.uk/projects/squish/home for tool to pack lua scripts.
- Sample code: http://lua-users.org/wiki/SampleCode
