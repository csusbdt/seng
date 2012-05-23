Project Setup {#setup}
=============

The setup instructions are only for Windows at this point.
We will add instructions for OS X setup in future.

Project Setup on Windows
------------------------

### Prequisites

- To build the C++ code and generate an executable, you need to have 
  Visual Studio 2010 installed with support for C++.  

- If you want to regenerate the documentation, you need to have Doxygen installed.

- If you want to develop the Lua scripts that define the application, 
  you don't need anything more than the project files (if they include a build of
  the project).

### Building

- No additional configuration is needed to build the project;
  just double click on the file platforms\vs2010\vs2010.sln.

### Running (debugging)

- Set the working directory of the main project to the working folder.
  To do this, add the following to the working directory field in the 
  Debugging section of the project properties for the main project.
  
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  \code
  $(ProjectDir)\..\..\..\..\working
  \endcode
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  