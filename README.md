# GameEngine
A component based game engine utilizing SDL2 and a component based architecture in C++.

Currently, only the underlying architecture and graphics system have been completed; compiling the project will produce a simple demo.

## Setup
This project requires an installation of SDL2 and SDL2_image to be compiled.
The included Makefile is built for Windows users utilizing MinGW. In this setup, place the DLLs for SDL2 and SDL2_image in the root directory of the project. In the Makefile, modify the INCLUDE and LIBS variables to the location of the respective folders in the SDL2 download.

Other systems will need to follow the instructions provided for their system on the SDL wiki at http://wiki.libsdl.org/Installation. If you decide to build on other systems using the included Makefile, remove the -Wl,-subsystem,windows flag under CPPFLAGS and -mwindows under LINKFLAGS.
