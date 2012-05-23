Project Notes {#notes}
=============

Git Setup
---------

I will provide read access to a project repo through Dropbox public folder.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\code

cd /Users/turner/Dropbox/Public
git --bare init

\endcode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Building
--------

- No additional configuration is needed to build the project;
  just double click on the file platforms\vs2010\vs2010c.sln.

Running (debugging)
-------------------

- Set the working directory of the main project to the working folder.
  To do this, add the following to the working directory field in the 
  Debugging section of the project properties for the main project.
  
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  \code
  $(ProjectDir)\..\..\..\..\working
  \endcode
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  
