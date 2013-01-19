OpenGL Kikoff
=============

Coding along with tutorials on modern OpenGL.

Creating a simple OpenGL framework.

Libraries and Tools
-------------------

* CMake
* SDL 2
* OpenGL

How-To Build (Mac OS X)
------------

#. Download SDL 2 to project's libs folder:

    cd libs
    hg clone http://hg.libsdl.org/SDL sdl

#. Build SDL localy:

    cd sdl
    mkdir build
    cd build   
    ../configure --prefix=`pwd`/../local
    make && make install

#. Generate project:

    cd `project-dir`
    cmake -G Xcode .

#. Build and run GoOpenGL target.

Acknowledgements
----------------

http://www.arcsynthesis.org/gltut/ - Clear and detailed tutorials on OpenGL 3.0

http://immersedcode.org/2011/4/6/sdl13-intro - Configuring CMake project with SDL 1.3