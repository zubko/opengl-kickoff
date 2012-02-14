OpenGL Kikoff
=============

Coding along with tutorials on modern OpenGL.

Creating a simple OpenGL framework.

Libraries and Tools
-------------------

* CMake
* SDL 1.3
* OpenGL

How-To Build
------------

1. Download SDL 1.3 to libs/sdl-1.3:

    cd libs
    hg clone http://hg.libsdl.org/SDL sdl-1.3

2. Apply patch at libs/sdl-1.3-opengl-3.0-patch.diff

3. Build SDL localy:

    cd sdl-1.3
    ./configure --prefix=`pwd`/local
    make && make install

4. Generate project:

    OS X:
    cmake -G Xcode

5. Build and run GoOpenGL target.

Acknowledgements
----------------

http://www.arcsynthesis.org/gltut/ - Clear and detailed tutorials on OpenGL 3.0

http://immersedcode.org/2011/4/6/sdl13-intro - Configuring CMake project with SDL 1.3