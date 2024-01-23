# simulations
Various physics simulations in C.

Settings for the simulations can be changed in the corresponding header files. 

Install requirements using:

```sudo apt install binutils clang gnuplot mingw-w64```

The animations require Raylib. To compile for Raylib Linux, follow the steps on https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux. 
Make sure to uncomment the line '#define SUPPORT_CUSTOM_FRAME_CONTROL 1' in raylib/src/config.h before building Raylib. 
To compile for Windows, change the CC and AR variables in raylib/src/Makefile into the MinGW versions. This Windows compilation of Raylib doesn't have to be installed, 
but the raylib folder needs to be included in the root directory of this project.  

To run i.e. a simulation of the Ising model, use the command ```make ising```.
