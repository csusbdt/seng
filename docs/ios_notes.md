Project Notes {#ios_notes}
=============

OpenGL ES 1.1 => fixed function pipeline
OpenGL ES 2.0 => programmable pipeline

Quartz == the OSX window system.  Ways to interact with OpenGL in Quartz: 
	- CGL
	- AGL
	- NSOpenGLView

Windows has WGL API to intereact with OpenGL


"OpenGL ES 2.0 is supported by most Android devices and is recommended 
for new applications being developed with OpenGL."
From http://developer.android.com/guide/topics/graphics/opengl.html
 
"OpenGL ES 2.0 is more flexible and more powerful than OpenGL ES 1.1 
and is the best choice for new applications."
From http://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/OpenGLES_ProgrammingGuide.pdf




Open GL Compatibility Guide
   http://www.opengl.org/registry/doc/glspec42.compatibility.20110808.pdf


The Khronos Native Platform Graphics Interface or “EGL Speciﬁcation” 
describes the EGL API for use of OpenGL ES on mobile and embedded devices.

OpenGL ES Programming Guide
    http://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/OpenGLES_ProgrammingGuide.pdf



Guidelines:

(1) On program start up, verify that required OpenGL features are supported.

(2) Applications that accesses the graphics processor while running in the
    background are automatically terminated by iOS. To avoid this, flush
    any pending commands previously submitted to OpenGL ES prior to being 
    moved into the background and wait until it is moved back to the
    foreground.

(3) 