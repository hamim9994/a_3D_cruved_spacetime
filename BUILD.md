This project uses OpenGL and FreeGLUT to visualize gravitational lensing and spacetime curvature.
Below are the build instructions for Windows and Linux.

✅ Requirements

C++ compiler (MSVC, GCC, or Clang)

OpenGL development libraries

FreeGLUT (or GLUT)

Git (optional)

🪟 Windows (Visual Studio) Build Instructions

Install Visual Studio
Use any version with C++ Desktop Development workload.

Install FreeGLUT
Download precompiled binaries:
https://www.transmissionzero.co.uk/software/freeglut-devel/

Extract FreeGLUT and place the following files:

include/GL/* → C:\Program Files\freeglut\include\GL\

lib/freeglut.lib → C:\Program Files\freeglut\lib\

bin/freeglut.dll → Place next to your .exe or in C:\Windows\System32

Open the Visual Studio project

Open the .sln or .vcxproj inside this repo.

Configure project paths
Go to:
Project → Properties → VC++ Directories

Include Directories:
C:\Program Files\freeglut\include

Library Directories:
C:\Program Files\freeglut\lib

Link required libraries
Project → Properties → Linker → Input → Additional Dependencies:
